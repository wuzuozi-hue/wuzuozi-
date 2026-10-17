#include <iostream>
#include <thread>
#include <vector>

// 练习：在新线程里计算 input * 2，并在返回前等线程结束。
// 目标：亲手使用 std::thread、按引用捕获、join。
int doubleInThread(int input) {
    int result = 0;
    std::thread worker([&]{result = input*2;});
    // TODO 1：创建名为 worker 的 std::thread。
    // 线程要通过 [&] 捕获，使 result = input * 2。
    worker.join();
    // TODO 2：等待 worker 完成。

    return result;
}

int main() {
    struct Case { int input; int expected; };
    const std::vector<Case> cases{{4, 8}, {-3, -6}, {0, 0}};
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const int got = doubleInThread(cases[i].input);
        const bool ok = got == cases[i].expected;
        if (ok) ++passed;
        std::cout << "case " << i + 1 << (ok ? " PASS" : " FAIL")
                  << " (got " << got << ", expected " << cases[i].expected << ")\n";
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
