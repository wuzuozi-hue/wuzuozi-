# Linux 操作系统基础：进程、线程、文件描述符

目标：能用代码观察创建/退出/等待，区分进程与线程、用户态对象与内核资源，并解释服务为什么会阻塞。来源：L05《进程概念》、L06《进程控制》、L07《基础 IO》、L02《线程概念与控制》、L03《线程同步与互斥》。先会用 [Linux 指令表](linux-commands.md) 的 `ps`、`pgrep`、`ls`、`ss`。

## 1. 进程与线程

进程是运行中程序及其资源的管理单位；线程是进程内的执行流。同一进程的线程共享地址空间和打开的文件等进程资源，但各有执行栈和寄存器状态。`fork()` 创建子进程后，父子进程拥有各自的地址空间视图；共享同一物理页直到写入触发写时复制，是常见实现优化。不要把“`fork` 后内存立刻完整拷贝”当成必然。

[进程状态转换图](../assets/figures/linux-process-states_L05_p11.png) 帮助区分就绪、运行、等待和结束。图是教学模型；Linux 工具可能显示 `R`、`S`、`D`、`T`、`Z` 等具体状态。子进程结束后若父进程未取走退出状态，会暂留僵尸状态；`waitpid` 负责回收退出状态。

```cpp
// fork_wait.cpp  Linux: g++ -std=c++17 -Wall -Wextra fork_wait.cpp -o fork_wait
#include <cerrno>
#include <cstdio>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    const pid_t child = fork();
    if (child < 0) { std::perror("fork"); return 1; }
    if (child == 0) {
        std::printf("child pid=%ld\n", static_cast<long>(getpid()));
        std::fflush(stdout); // 只冲刷本例子进程刚写出的内容
        _exit(7); // 不运行继承自父进程的 stdio 清理逻辑
    }
    int status = 0;
    if (waitpid(child, &status, 0) < 0) { std::perror("waitpid"); return 1; }
    if (WIFEXITED(status)) {
        std::printf("parent saw exit=%d\n", WEXITSTATUS(status));
    }
}
```

父进程会等到子进程退出后才打印退出码。本例不要在 `fork` 之前留下未冲刷的 `stdout` 内容，否则父子进程各自持有缓冲区副本，显式冲刷也可能造成重复输出。`exec` 系列调用是把当前进程的程序映像替换成新程序，并非创建一个新进程；常见组合是 `fork → 子进程 exec → 父进程 waitpid`。

## 2. 文件描述符与 I/O

文件描述符是进程内引用打开文件/管道/socket 的小整数；`0/1/2` 通常对应标准输入/输出/错误。`open()` 成功返回描述符，失败返回 `-1`；`read()`/`write()` 的返回值可能小于请求长度，网络尤其不能假定一次收发完一条消息。重定向和管道依赖文件描述符及其复制（L07）。

```cpp
// read_file.cpp  Linux: g++ -std=c++17 -Wall -Wextra read_file.cpp -o read_file
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) { std::perror("open"); return 1; }
    char buffer[256];
    for (;;) {
        ssize_t n = read(fd, buffer, sizeof buffer);
        if (n > 0) {
            ssize_t done = 0;
            while (done < n) {
                ssize_t written = write(STDOUT_FILENO, buffer + done, n - done);
                if (written < 0 && errno == EINTR) continue;
                if (written < 0) { std::perror("write"); close(fd); return 1; }
                if (written == 0) { std::fputs("write returned 0\n", stderr); close(fd); return 1; }
                done += written;
            }
        } else if (n == 0) {
            break; // 文件末尾
        } else if (errno != EINTR) {
            std::perror("read"); close(fd); return 1;
        }
    }
    close(fd);
}
```

运行前用 `printf 'hello\n' > sample.txt` 创建测试数据。练习版手写 `close` 是为了观察系统调用；真实 C++ 服务应使用 RAII 包装描述符，确保异常/提前返回也释放。

## 3. 线程与互斥

多个线程并发写同一非原子变量而没有同步，是数据竞争，C++ 程序行为未定义。`std::mutex` 与 `std::lock_guard` 用于保护临界区；加锁后才能保证以下计数程序的最终结果。

```cpp
// counter.cpp  Linux: g++ -std=c++17 -Wall -Wextra -pthread counter.cpp -o counter
#include <iostream>
#include <mutex>
#include <thread>

int main() {
    int count = 0;
    std::mutex mutex;
    auto task = [&] {
        for (int i = 0; i < 10000; ++i) {
            std::lock_guard<std::mutex> lock(mutex);
            ++count;
        }
    };
    std::thread a(task), b(task);
    a.join();
    b.join();
    std::cout << count << '\n'; // 20000
}
```

项目关联：如果模型请求在处理线程中耗时 30 秒，事件循环线程仍须能响应 `/health`；共享任务状态必须明确由哪把锁或哪个线程保护。下一步在 [操作系统进阶](linux-os-advanced.md) 学条件变量、有界队列、`mmap` 与 IPC。

面试自测：`fork()` 在父子进程分别返回什么？为什么子进程退出后还要 `waitpid`？线程为什么必须 `join` 或 `detach`？`read()` 返回 0、正数和 -1 分别代表什么？
