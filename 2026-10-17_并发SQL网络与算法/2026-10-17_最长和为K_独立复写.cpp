#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
// 2026-10-17 独立复写：最长和为 K 的连续子数组
// 数组可能有负数和 0；没有符合条件的连续子数组时返回 0。
// 目标：写出平均 O(n) 的方法，并解释为何同一前缀和要保留最早下标。
// 今天先不看昨日的讲解版，独立写完后再运行下面的测试。
int longestSubarraySumK(const std::vector<int>& nums, int k) {
    // 在这里写你的实现。
    std::unordered_map<long long,int>prefixcount;
    int n = nums.size();
    prefixcount[0] = -1;
    long long prefix =0;
    int count = 0;
    for(int i =0; i<n;i++){
        prefix += nums[i];
        long long need = prefix - k;
        auto it = prefixcount.find(need);
        if(it!=prefixcount.end()){
            count =std::max(count,i-it->second);
        }
        if(prefixcount.count(prefix) == 0){
            prefixcount[prefix] = i;
        }
    }
    return count;
}

int main() {
    struct Case {
        std::vector<int> nums;
        int k;
        int expected;
    };

    const std::vector<Case> cases{
        {{2, -1, 2, 1, -2, 3}, 3, 5},
        {{4, -1, -1, 2, -2, 2}, 2, 5},
        {{0, 0, 0, 0}, 0, 4},
        {{-2, 5, -1, 2, -4}, 4, 4},
        {{1, 2, 3}, 7, 0},
        {{}, 3, 0},
    };

    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        int got = longestSubarraySumK(cases[i].nums, cases[i].k);
        bool ok = got == cases[i].expected;
        if (ok) ++passed;
        std::cout << "case " << i + 1 << (ok ? " PASS" : " FAIL")
                  << " (got " << got << ", expected " << cases[i].expected << ")\n";
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
