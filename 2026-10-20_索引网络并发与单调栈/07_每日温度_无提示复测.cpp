// 2026-10-20：每日温度无提示复测。
// 规则：先不要查看 03_每日温度_单调栈练习.cpp；独立实现下面的函数。
#include <iostream>
#include <vector>

std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    // 在这里独立实现。
    int n = temperatures.size();
    std::vector<int> answer(n, 0);
    std::vector<int> waiting;
    int today = 0;
    for(today = 0;today<n;today++){
        while(!waiting.empty()&& temperatures[today] >temperatures[waiting.back()]){
            int early = waiting.back();
            waiting.pop_back();
            answer[early] =today -early;
        }
        waiting.push_back(today);
    }
    return answer;
}
// 30 28 31
//  0  1  2
//  2  1  0
struct TestCase {
    const char* name;
    std::vector<int> input;
    std::vector<int> expected;
};

int main() {
    const std::vector<TestCase> cases{
        {"sample", {73, 74, 75, 71, 69, 72, 76, 73}, {1, 1, 4, 2, 1, 1, 0, 0}},
        {"decreasing", {75, 74, 73}, {0, 0, 0}},
        {"equal", {30, 30, 30}, {0, 0, 0}},
        {"empty", {}, {}},
        {"rising_after_drop", {30, 28, 31}, {2, 1, 0}},
    };

    int passed = 0;
    for (const auto& test : cases) {
        const bool ok = dailyTemperatures(test.input) == test.expected;
        std::cout << test.name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (ok) ++passed;
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
