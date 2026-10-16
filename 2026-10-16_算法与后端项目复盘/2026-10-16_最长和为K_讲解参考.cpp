#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// 2026-10-16：在提示下完成的讲解版。前缀和 -> 首次出现的下标。
int longestSubarraySumK(const std::vector<int>& nums, int k) {
    std::unordered_map<long long, int> firstIndex;
    firstIndex[0] = -1;
    long long prefix = 0;
    int best = 0;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        prefix += nums[i];
        const long long need = prefix - k;
        const auto it = firstIndex.find(need);
        if (it != firstIndex.end()) {
            best = std::max(best, i - it->second);
        }
        if (firstIndex.find(prefix) == firstIndex.end()) {
            firstIndex[prefix] = i;
        }
    }
    return best;
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
