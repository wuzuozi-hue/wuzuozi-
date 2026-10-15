# Linux 网络进阶：连接状态、I/O 多路复用与 Reactor

前置：能运行 [单连接 TCP 示例](linux-network-basic.md)，并解释 TCP 是字节流。来源：L22—L29、L35—L48，尤其 L25 I/O 模型、L26—L28 多路复用、L29 Reactor、L43 TCP、L44 抓包。

## 1. TCP 连接在故障中的表现

[TCP 生命周期图](../assets/figures/network-tcp-lifecycle_L43_p6.png) 把三次握手、数据传输与关闭状态连在一起。`CLOSE_WAIT` 长期不消失常提示本端收到对端 FIN 后未及时关闭连接；`TIME_WAIT` 通常出现在主动关闭的一方，不能一看到就当作内存泄漏。具体状态用 `ss -tan` 查看，再对照应用日志和抓包确认。

```bash
ss -tan | grep ':18880'
sudo tcpdump -i any -nn 'tcp port 18880'
```

重传、拥塞控制、接收窗口和应用处理慢都可能表现为请求耗时。先区分“连接建立慢”“发送/接收慢”“服务内处理慢”“下游模型慢”，不能只凭一次总耗时断定 TCP 原因（L43—L44）。

## 2. I/O 多路复用：`select`、`poll`、`epoll`

| 机制 | 程序交给内核的内容 | 学习重点 |
|---|---|---|
| `select` | 描述符集合，每轮更新集合 | `fd_set` 容量、最大 fd、返回后集合被改写。 |
| `poll` | `pollfd` 数组 | 没有 `fd_set` 固定集合接口，仍需逐个查看返回事件。 |
| `epoll` | 先注册关注的 fd，再等待就绪事件 | 区分注册、等待、读取；理解水平触发 LT 与边缘触发 ET。 |

多路复用让一个线程等待多个 I/O 事件，**不会让 CPU/GPU 模型计算自动变快**。课件 [epoll 结构图](../assets/figures/network-epoll-structure_L28_p6.png) 是教学示意，实际内核内部结构依版本变化；接口语义和程序行为比背某个内部容器更重要。

```cpp
// epoll_pipe.cpp  Linux: g++ -std=c++17 -Wall -Wextra epoll_pipe.cpp -o epoll_pipe
#include <cstdio>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
    int ends[2];
    if (pipe(ends) < 0) { std::perror("pipe"); return 1; }
    int ep = epoll_create1(EPOLL_CLOEXEC);
    if (ep < 0) { std::perror("epoll_create1"); close(ends[0]); close(ends[1]); return 1; }
    epoll_event wanted{};
    wanted.events = EPOLLIN;
    wanted.data.fd = ends[0];
    if (epoll_ctl(ep, EPOLL_CTL_ADD, ends[0], &wanted) < 0) {
        std::perror("epoll_ctl"); close(ep); close(ends[0]); close(ends[1]); return 1;
    }
    if (write(ends[1], "A", 1) != 1) {
        std::perror("write"); close(ep); close(ends[0]); close(ends[1]); return 1;
    }
    epoll_event ready{};
    int count = epoll_wait(ep, &ready, 1, 1000);
    if (count < 0) { std::perror("epoll_wait"); close(ep); close(ends[0]); close(ends[1]); return 1; }
    if (count == 0) { std::fputs("epoll_wait timed out\n", stderr); close(ep); close(ends[0]); close(ends[1]); return 1; }
    char value = 0;
    if (read(ready.data.fd, &value, 1) != 1) { std::perror("read"); close(ep); close(ends[0]); close(ends[1]); return 1; }
    std::printf("ready: %c\n", value); // ready: A
    close(ep); close(ends[0]); close(ends[1]);
}
```

这个实验用管道代替 Socket，单独验证“注册 → 事件就绪 → 等待返回 → 读取”。随后再把已会用的 TCP 连接放进事件循环。ET 模式下应把 fd 设为非阻塞，并反复读/写直到 `EAGAIN`；一次 `recv` 后就等下一次边缘事件，可能使已到达的数据长期留在缓冲区（L28）。

## 3. Reactor、协议边界与超时

Reactor 把“某个 fd 就绪”分派给对应处理逻辑。回调注册后对象可能先被销毁，因此必须分析**回调的所有权、取消、关闭 fd 与重新注册**；不要在事件循环回调中同步等待耗时 AI 服务。课件 L29 是 Reactor 设计参考，真正使用框架时以框架接口与线程模型为准。

TCP 没有消息边界。若设计长度前缀协议，需先读完整固定长度的头，转换网络字节序，检查声明长度的上限，再按循环读满正文；否则半包/粘包、超大长度和提前断开都会出错。HTTP 框架已处理大量协议细节，业务层仍要限制上传大小和验证内容类型（L36—L39）。

超时最好分层记录：连接超时、读写超时、下游模型超时、任务总截止时间。一个任务超时不等于立即能停止已经发出的外部计算；状态、重试与幂等要单独设计。项目里要用固定延迟的模拟模型测队列满比例，再单独记录真实模型耗时。

面试自测：LT 与 ET 为什么需要不同的读取循环？`epoll_wait` 返回“可读”是否保证一次 `recv` 能读完完整请求？服务 `CLOSE_WAIT` 很多时你先查哪段代码？
