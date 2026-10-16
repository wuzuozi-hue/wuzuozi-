#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// 2026-10-16 练习：最长和为 k 的连续子数组
// 例如 nums={1,-1,5,-2,3}, k=3，答案为 4：{1,-1,5,-2}。
// 数组可能含负数；不存在时返回 0。目标时间复杂度 O(n)。

int longestSubarraySumK(const std::vector<int>& nums, int k) {
    // 思考：计数题里哈希表保存“前缀和 -> 出现次数”。
    // 本题要最长长度，同一个前缀和应该保留最早还是最近的下标？
    // 提示：把数组开始前的前缀和 0 看作位于下标 -1。
    //  1 0  5  3  6
    //  0 1  2  3  4
    std::unordered_map<long long ,int> prefixcount;
    long long prefix = 0;
    prefixcount[0] = -1;
    int n = nums.size();
    int count = 0;
    for(int i =0; i<n ; i++){
        prefix += nums[i];
        if(prefix == k){
            count = std::max(count,i+1);
        }
        prefixcount[prefix] = i;
    }
    return count;
}

int main() {
    struct Case { std::vector<int> nums; int k; int expected; };
    const std::vector<Case> cases{
        {{1, -1, 5, -2, 3}, 3, 4},
        {{5, -2, 4, -2}, 2, 2},
        {{0, 0, 0}, 0, 3},
        {{3}, 3, 1},
        {{}, 7, 0},
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const int got = longestSubarraySumK(cases[i].nums, cases[i].k);
        const bool ok = got == cases[i].expected;
        passed += ok;
        std::cout << "case " << i + 1 << (ok ? " PASS" : " FAIL")
                  << " (got " << got << ", expected " << cases[i].expected << ")\n";
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
}
