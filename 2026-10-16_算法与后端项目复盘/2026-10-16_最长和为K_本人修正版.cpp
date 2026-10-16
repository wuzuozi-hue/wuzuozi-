#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// 按聊天中贴出的版本留档；不覆盖 VS Code 中未保存的练习文件。
int longestSubarraySumK(const std::vector<int>& nums, int k) {
    std::unordered_map<long long ,int> prefixcount;
    long long prefix = 0;
    prefixcount[0] = -1;
    int n = nums.size();
    int count = 0;
    for(int i =0; i<n ; i++){
        prefix += nums[i];
        long long need = prefix - k;
        auto it = prefixcount.find(need);
        if(it!=prefixcount.end()){
            count =std::max(count,i-prefixcount[need]);
        }
        if(prefixcount.count(prefix) == 0)
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
