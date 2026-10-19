// 2026-10-19 18:10：滑动窗口无提示复测
// 目标：最长连续子数组中，最多包含 k 种不同数字。
// 当晚复测版本：本人实现并在反馈后修正了窗口收缩和最优值更新。

#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
int longestAtMostKTypes(const std::vector<int>& nums, int k) {
    std::unordered_map<int,int> cnt;
    int n =nums.size();
    int left = 0;
    int right = 0;
    int best =0;
    if(k<=0){
        return 0;
    }
    if(nums.size() ==0){
        return 0;
    }
    for(right = 0;right<n;right++){
        cnt[nums[right]]++;
        while(cnt.size() > k){
            int old = nums[left];
            --cnt[old];
            if(cnt[old] == 0){
                cnt.erase(old);
            }
             ++left;
        }
        int length = right -left +1;
        best =std::max(best,length);
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
        {{4, 4, 1, 2, 2, 1, 1}, 2, 5},
        {{1, 2, 3}, 1, 1},
        {{1, 2, 3}, 0, 0},
        {{}, 2, 0},
        {{5, 5, 5}, 1, 3},
        {{1, 2, 1, 3, 4, 3}, 2, 3},
        {{1, 1, 2, 2, 3}, 2, 4}, // 最长窗口不在末尾：不能用较短的最终窗口覆盖 best
        {{1, 2, 3}, -1, 0},       // 非正 k 没有有效窗口
    };

    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const int actual = longestAtMostKTypes(cases[i].nums, cases[i].k);
        if (actual == cases[i].expected) {
            ++passed;
        } else {
            std::cout << "case " << i + 1 << ": expected " << cases[i].expected
                      << ", got " << actual << '\n';
        }
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
