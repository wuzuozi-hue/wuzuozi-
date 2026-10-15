# Linux 网络基础：从 TCP 字节流到 HTTP 接口

目标：能解释请求如何从应用到 Socket、TCP、IP、网卡，再回到服务端；能写一个单连接 TCP 程序，分辨“连接建立”与“业务成功”。来源：L21 网络基础、L30/L33 Socket 编程、L39 HTTP、L42/L43 UDP/TCP、L45/L47 网络层与链路层。

## 1. 分层与地址

[OSI 上半页](../assets/figures/network-osi-upper_L21_p7.png) 和 [下半页](../assets/figures/network-osi-lower_L21_p8.png) 适合定位故障：应用层是 HTTP；传输层是 TCP/UDP 和端口；网络层是 IP 与路由；链路层负责同一链路的帧交付。OSI 七层与工程中常用的 TCP/IP 分层只是不同抽象，不应说成“实际网络包里有七层字段”。

`127.0.0.1` 是本机回环地址。服务只绑定 `127.0.0.1:9000` 时，其他机器不能直接访问；若绑定 `0.0.0.0:9000`，则在所有 IPv4 网卡监听，还受防火墙与权限影响。`bind` 选择本地地址与端口，`connect` 发起连接；同一机器上的端口仍要区分不同服务。

## 2. TCP 与 UDP

TCP 提供有序、可靠的**字节流**；一次 `send` 与一次 `recv` 不存在一一对应消息边界。应用层要自己设计分帧，例如固定长度、分隔符或长度前缀。UDP 是数据报，保留报文边界，但应用层需处理丢包、乱序与重复等问题。不要把“UDP 一定更快”“TCP 一定不会断”当作保证。

TCP 服务器常见调用顺序：`socket → bind → listen → accept → recv/send → close`；客户端：`socket → connect → send/recv → close`。参看 [TCP 连接与关闭时序图](../assets/figures/network-tcp-lifecycle_L43_p6.png)。`accept` 成功后得到**新连接描述符**，原监听描述符继续负责接收新连接。

```cpp
// echo_server.cpp  仅供单连接练习：Linux g++ -std=c++17 -Wall -Wextra echo_server.cpp -o echo_server
#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) { std::perror("socket"); return 1; }
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(9000);
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(server, reinterpret_cast<sockaddr*>(&address), sizeof address) < 0) {
        std::perror("bind"); close(server); return 1;
    }
    if (listen(server, 8) < 0) {
        std::perror("listen"); close(server); return 1;
    }
    int client = accept(server, nullptr, nullptr);
    if (client < 0) { std::perror("accept"); close(server); return 1; }
    char data[4096];
    for (;;) {
        ssize_t n = recv(client, data, sizeof data, 0);
        if (n < 0 && errno == EINTR) continue;
        if (n == 0) break; // 对端正常关闭发送方向
        if (n < 0) { std::perror("recv"); close(client); close(server); return 1; }
        for (ssize_t sent = 0; sent < n;) {
            ssize_t k = send(client, data + sent, n - sent, MSG_NOSIGNAL);
            if (k < 0 && errno == EINTR) continue;
            if (k < 0) { std::perror("send"); close(client); close(server); return 1; }
            if (k == 0) { std::fputs("send returned 0\n", stderr); close(client); close(server); return 1; }
            sent += k;
        }
    }
    close(client);
    close(server);
}
```

用 `ss -ltnp | grep ':9000'` 检查监听。可用 Python 标准库作为测试客户端：

```bash
python3 - <<'PY'
import socket
with socket.create_connection(('127.0.0.1', 9000), timeout=3) as s:
    s.sendall(b'hello')
    s.shutdown(socket.SHUT_WR)
    chunks = []
    while True:
        chunk = s.recv(100)
        if not chunk:
            break
        chunks.append(chunk)
    print(b''.join(chunks))  # b'hello'；不能假定一次 recv 收齐
PY
```

这只是一次接一条连接的教学程序：没有超时、并发、协议边界或优雅停机设计。实际服务使用框架的异步网络接口；到 [网络进阶](linux-network-advanced.md) 再看 `epoll` 与 Reactor。

## 3. HTTP 与后端接口

HTTP 请求由方法、路径、头和可选正文组成；响应有状态码、头和正文。TCP 连接成功只说明传输层可通信；`GET /health` 返回 `200`、`POST /v1/questions` 返回 `202`、提交队列满返回 `503` 是应用层决定的结果。`202 Accepted` 只表示已接受处理，不保证后台任务成功。

```bash
curl -i http://127.0.0.1:18880/health
curl -i -X POST http://127.0.0.1:18880/v1/questions \
  -H 'Content-Type: application/json' \
  -H 'X-API-Key: <演示密钥>' \
  --data '{"question":"什么是 RAII？"}'
```

第二个请求须换成自己的本地演示密钥；不要把密钥写进仓库或日志。若接口超时，按 DNS（若有域名）→目标 IP/端口→TCP 连接→HTTP 状态→服务日志→下游依赖的顺序定位，不要一开始就判断“网络坏了”。

面试自测：TCP 为什么要应用层分帧？`listen` 的 fd 和 `accept` 返回的 fd 有什么区别？`202` 与后台任务成功是什么关系？
