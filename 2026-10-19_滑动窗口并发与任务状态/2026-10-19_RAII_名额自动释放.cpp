// 2026-10-19 C++ 基础：局部对象析构与 RAII
// 练习作用域退出和异常展开时，SlotGuard 析构释放名额。

#include <iostream>
#include <stdexcept>

struct Counter {
    int used = 0;
    int releaseCalls = 0;

    void reserve() { ++used; }
    void release() {
        --used;
        ++releaseCalls;
    }
};

struct SlotGuard {
    Counter& counter;

    explicit SlotGuard(Counter& c) : counter(c) {}

    ~SlotGuard() {
        counter.release();
    }
};

int earlyReturn(Counter& counter) {
    counter.reserve();
    SlotGuard guard(counter);
    return 202;
}

void exceptionPath(Counter& counter) {
    counter.reserve();
    SlotGuard guard(counter);
    throw std::runtime_error("database failed");
}

int main() {
    Counter first;
    const int status = earlyReturn(first);
    std::cout << "return: status=" << status << " used=" << first.used
              << " releases=" << first.releaseCalls << '\n';

    Counter second;
    try {
        exceptionPath(second);
    } catch (const std::runtime_error&) {
        std::cout << "exception: used=" << second.used
                  << " releases=" << second.releaseCalls << '\n';
    }

    return (first.used == 0 && first.releaseCalls == 1 &&
            second.used == 0 && second.releaseCalls == 1) ? 0 : 1;
}
