// 2026-10-21：在双层循环版本通过后，再做循环数组的单调栈版本。
// 返回每个位置向右（可绕回开头）遇到的第一个严格更大的数；找不到填 -1。
#include <iostream>
#include <vector>

std::vector<int> nextGreaterCircularStack(const std::vector<int>& nums) {
    // TODO：参考“每日温度”的等待下标栈，但数组需要观察两圈。
    // 提问：第二圈是否还要把下标压入等待栈？
    int n = static_cast<int>(nums.size());
    std::vector<int> ans(n,-1);
    std::vector<int> waiting;
    for(int step = 0; step < 2 * n; step++){
        int j = step%n;
        while(!waiting.empty() &&nums[j] > nums[waiting.back()]){
            int early = waiting.back();
            ans[early] = nums[j];
            waiting.pop_back();
        }
        if(step <n)
        waiting.push_back(j);

    }
    return ans;
}

struct TestCase {
    const char* name;
    std::vector<int> input;
    std::vector<int> expected;
};

int main() {
    const std::vector<TestCase> cases{
        {"empty", {}, {}},
        {"single", {8}, {-1}},
        {"wrap", {1, 2, 1}, {2, -1, 2}},
        {"cross_boundary", {3, 1, 2}, {-1, 2, 3}},
        {"equal", {5, 5}, {-1, -1}},
        {"descending", {4, 3, 2, 1}, {-1, 4, 4, 4}},
        {"multiple_pop", {2, 1, 3}, {3, 3, -1}},
    };
    int passed = 0;
    for (const auto& test : cases) {
        const bool ok = nextGreaterCircularStack(test.input) == test.expected;
        std::cout << test.name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (ok) ++passed;
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
