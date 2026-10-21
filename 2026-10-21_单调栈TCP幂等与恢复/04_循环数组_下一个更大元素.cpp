// 2026-10-21：循环数组中每个数右侧第一个严格更大的数；没有则为 -1。
// 先写容易验证的正确版本，再讨论是否要改为单调栈。
#include <iostream>
#include <vector>

std::vector<int> nextGreaterElements(const std::vector<int>& nums) {
    // TODO：独立实现。空数组应返回空数组。
    int n = nums.size();
    std::vector<int> ans(n,-1);
    for(int i = 0 ;i<n;i++){
        for(int step =1;step<n;step++){
            int j = (i+step) % n;
            if(nums[i] < nums[j]){
                ans[i] = nums[j];
                break;
            }
        }
    }
    return ans;
}
//0 1 2 3 4 5 6 7
//4 2 1 1 1 1 1 3
//-1 3 4
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
    };
    int passed = 0;
    for (const auto& test : cases) {
        const bool ok = nextGreaterElements(test.input) == test.expected;
        std::cout << test.name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (ok) ++passed;
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
