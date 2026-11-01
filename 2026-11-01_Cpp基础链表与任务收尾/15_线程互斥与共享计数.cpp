#include <iostream>
#include <mutex>
#include <thread>

int main() {
    int completed = 0;
    std::mutex mutex;
    const int perWorker = 10000;

    auto work = [&]() {
        for (int i = 0; i < perWorker; ++i) {
            // TODO：使用 std::lock_guard<std::mutex> 在本轮保护 completed。
            std::lock_guard<std::mutex> lock(mutex);
            completed++;
            // 然后让 completed 加 1。锁应在本次循环结束时自动释放。
        }
    };

    // TODO：创建两个线程执行 work，并等待两个线程结束。
    std::thread thread1 (work);
    std::thread thread2 (work);

    thread1.join();
    thread2.join();
    // 正确完成后，两个线程总共处理 20000 次。
    std::cout << "completed: " << completed << '\n';
    std::cout << (completed == 2 * perWorker ? "PASS" : "FAIL") << '\n';
}
