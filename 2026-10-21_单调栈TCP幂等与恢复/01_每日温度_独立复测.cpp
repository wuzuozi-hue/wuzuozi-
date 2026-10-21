// 2026-10-21：独立复测。先不要打开昨天的参考实现。
// 返回每一天要等多少天才出现严格更高的温度；若不存在则为 0。
#include <iostream>
#include <vector>

std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    // 在这里独立编写；可以增加辅助容器。
    int n = temperatures.size();
    std::vector<int> ans(n,0);
    std::vector<int> waiting;//下标
    for(int today = 0; today<n;today++){
        while(!waiting.empty()&& temperatures[today]>temperatures[waiting.back()]){
            int early = waiting.back();
            waiting.pop_back();
            ans[early] = today - early;
        }
        waiting.push_back(today);
    }
    return ans;
}
//30 28 31 tem
// 0  1  2 waiting
// 2  1  0 ans
struct TestCase {
    const char* name;
    std::vector<int> input;
    std::vector<int> expected;
};

int main() {
    const std::vector<TestCase> cases{
        {"empty", {}, {}},
        {"single", {60}, {0}},
        {"descending", {80, 70, 60}, {0, 0, 0}},
        {"plateau_then_rise", {40, 40, 41}, {2, 1, 0}},
        {"several_waiting", {25, 22, 24, 21, 26}, {4, 1, 2, 1, 0}},
        {"zigzag", {10, 13, 12, 15}, {1, 2, 1, 0}},
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
