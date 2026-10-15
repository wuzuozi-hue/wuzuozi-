# Linux 操作系统进阶：虚拟内存、IPC 与同步

前置：能解释 [进程、线程和文件描述符](linux-os-basic.md)，会用 `ps`/`ss` 看现象。来源：L02—L03、L08—L20、L25。重点服务于任务调度、后台工作者、重启恢复和 I/O 阻塞分析。

## 1. 虚拟地址与写时复制

每个进程看到自己的虚拟地址空间，CPU 与内核通过页表等机制映射到物理内存；虚拟地址相同不代表物理页相同。`fork` 后父子进程初始内容看似相同，常通过写时复制减少立即拷贝成本。缺页、页缓存和文件映射会影响性能，但“虚拟内存 = 硬盘交换空间”是错误的简化（L05、L20）。

`mmap` 能把文件映射到地址空间，也能建立进程共享区域。映射并不自动解决并发更新：两个进程修改同一块共享内存时仍要同步。页映射与刷新时机需要按 `MAP_SHARED`/`MAP_PRIVATE`、文件系统和系统调用语义判断（L14—L15）。

## 2. 进程间通信怎么选

| 方式 | 特点 | 适合的练习 |
|---|---|---|
| 匿名管道 | 字节流，常用于有亲缘关系的进程 | 父进程把任务文本传给子进程。 |
| 命名管道 FIFO | 有路径名，独立进程也能打开 | 本机两个命令行程序通信。 |
| 共享内存 / `mmap` | 相比经管道传递，可避免部分进程间数据搬运；仍需同步 | 共享固定大小的状态区。 |
| 消息队列 | 传离散消息，由内核管理队列 | 按消息类型传任务。 |
| Socket | 可跨主机，按 TCP/UDP 语义通信 | C++ API 调 Python AI 服务。 |

来源 L10、L14—L17。DevDocQA 当前 C++ 与 Python 使用内部 HTTP，属于 Socket 上的应用层协议；这比本机共享内存更容易隔离故障和观察请求，但有序列化与网络调用成本。

## 3. 锁、条件变量和有界队列

互斥锁保护共享状态，条件变量用于“条件不满足时释放锁并等待，条件变化后重新检查”。等待必须在循环或带谓词的 `wait` 中检查，原因包括虚假唤醒与多个消费者竞争。队列容量需要明确：满时拒绝、阻塞还是丢弃；不能无限增长直到内存耗尽（L03）。

```cpp
// bounded_queue.cpp  Linux: g++ -std=c++17 -Wall -Wextra -pthread bounded_queue.cpp -o bounded_queue
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class BoundedQueue {
    const std::size_t capacity_ = 2;
    std::queue<int> data_;
    std::mutex mutex_;
    std::condition_variable changed_;
public:
    bool try_push(int value) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_.size() == capacity_) return false;
        data_.push(value);
        changed_.notify_one();
        return true;
    }
    int pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        changed_.wait(lock, [this] { return !data_.empty(); });
        int value = data_.front();
        data_.pop();
        return value;
    }
};

int main() {
    BoundedQueue queue;
    queue.try_push(10);
    queue.try_push(20);
    std::cout << std::boolalpha << queue.try_push(30) << '\n'; // false: 满
    std::thread worker([&] { std::cout << queue.pop() << '\n'; });
    worker.join();
}
```

教学代码只有一个消费者，未实现关闭/取消。生产队列必须定义停机时如何唤醒等待线程、如何处理超时，以及任务状态何时落库。面试追问重点：为何 `wait` 需要谓词？为何通知前后的状态更新需要同一把锁？队列满返回 `503` 与进程内存不足有何区别？

## 4. 信号、死锁与 I/O

信号是异步通知；信号处理函数内只能做异步信号安全的操作，不能随意调用 `std::cout`、拿普通互斥锁或做复杂分配。初学的**单线程**例子可只设置 `volatile sig_atomic_t` 退出标志，让主循环走正常清理路径；它不代替多线程共享状态同步。如果主循环阻塞在 `epoll_wait` 等调用中，还需要能唤醒它的机制，Linux 服务常使用 self-pipe、`eventfd` 或 `signalfd`（L11）。

死锁的典型条件包括互斥、持有并等待、不可抢占与循环等待。工程上通过固定加锁顺序、缩小临界区、使用 `std::scoped_lock` 同时获取多把锁，并在排查时画出等待图。`std::scoped_lock` 是 C++17；更复杂的锁方案见 L18—L19。

[I/O 模型时序图](../assets/figures/linux-io-models_L25_p3.png) 要分清两段时间：等待数据准备与把数据复制到用户空间。非阻塞 I/O 只改变“等待”的方式；模型推理的 CPU/GPU 计算本身仍可能很慢，应放在独立工作线程/服务中。`select`、`poll`、`epoll` 属于 [网络进阶](linux-network-advanced.md)。
