// 2026-10-19 算法迁移：最长连续子数组中至多 K 种数字
// 先独立实现，再编译运行。与“水果成篮”的区别是把固定的 2 改为参数 k。

#include <iostream>
#include <unordered_map>
#include <vector>

int longestAtMostKTypes(const std::vector<int>& nums, int k) {
    int n = nums.size();
    int left = 0;
    int right = 0;
    int best = 0;
    std::unordered_map<int,int> freq;
    if(k<=0){
        return 0;
    }
    for(right = 0; right <n ;right++){
        freq[nums[right]]++;
        while(freq.size() > static_cast<std::size_t>(k)){
            int old = nums[left];
            freq[old]--;
            if(freq[old] == 0){
                freq.erase(old);
            }
            ++left;
        }
        int length = right - left +1;
        if(length > best)
        best =length;
    }
    return best;
}

int main() {
    struct Case {
        std::vector<int> nums;
        int k;
        int expected;
    };
    const std::vector<Case> cases = {
        {{1, 2, 2, 3}, 1, 2},
        {{1, 2, 2, 3}, 2, 3},
        {{1, 2, 2, 3}, 3, 4},
        {{3, 3, 3}, 1, 3},
        {{1, 2, 3}, 0, 0},
        {{}, 2, 0},
    };

    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        int actual = longestAtMostKTypes(cases[i].nums, cases[i].k);
        if (actual == cases[i].expected) {
            ++passed;
        } else {
            std::cout << "case " << i + 1 << ": expected " << cases[i].expected
                      << ", got " << actual << '\n';
        }
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
}
