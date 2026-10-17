#include <iostream>
#include <mutex>
#include <thread>

// 两个线程会同时调用这个函数。
// 目标：让每次 count 加 1 都受到同一把 mutex 保护。
void safeIncrement(int& count, std::mutex& mutex) {
    // TODO 1：在这里创建 std::lock_guard<std::mutex>，锁住 mutex。
    std::lock_guard<std::mutex> lock(mutex);
    ++count;
    // TODO 2：将 count 加 1。
}

int runCase(int times) {
    int count = 0;
    std::mutex mutex;
    auto work = [&] {
        for (int i = 0; i < times; ++i) {
            safeIncrement(count, mutex);
        }
    };
    std::thread first(work);
    std::thread second(work);
    first.join();
    second.join();
    return count;
}

int main() {
    int passed = 0;
    for (int times : {1, 1000, 10000}) {
        const int got = runCase(times);
        const int expected = times * 2;
        const bool ok = got == expected;
        if (ok) ++passed;
        std::cout << "times=" << times << (ok ? " PASS" : " FAIL")
                  << " (got " << got << ", expected " << expected << ")\n";
    }
    std::cout << "passed " << passed << "/3\n";
    return passed == 3 ? 0 : 1;
}
