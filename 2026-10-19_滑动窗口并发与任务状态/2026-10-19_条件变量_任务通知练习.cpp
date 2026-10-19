// 2026-10-19 C++ 并发：条件变量通知一个工作线程
// 目标：工作线程等待任务；主线程提交数字 7；工作线程输出处理结果 14。

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
    std::mutex m;
    std::condition_variable cv;
    bool ready = false;
    int input = 0;
    int result = 0;

    std::thread worker([&] {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock,[&]{return ready;});
        int value = input; // 持锁读取主线程提交的数据。
        lock.unlock();     // 耗时处理不占着队列锁。
        result = value * 2;
    });

    {
        std::lock_guard<std::mutex> lock(m);
        input = 7;
        ready =true;
    }
    cv.notify_one();
    worker.join(); // 等工作线程结束后，再读取 result。
    std::cout << "result=" << result << '\n';
    return result == 14 ? 0 : 1;
}
