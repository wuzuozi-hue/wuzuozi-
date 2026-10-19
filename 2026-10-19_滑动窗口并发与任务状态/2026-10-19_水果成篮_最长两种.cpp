// 2026-10-17 算法收尾：水果成篮（LeetCode 904）
//
// 给定水果类型数组，找出只包含至多 2 种类型的最长连续子数组长度。
// 例如 {1, 2, 3, 2, 2} -> 4，对应 {2, 3, 2, 2}。
// 要求：滑动窗口，目标时间复杂度 O(n)。先自己写，再运行测试。

#include <iostream>
#include <unordered_map>
#include <vector>

int totalFruit(const std::vector<int>& fruits) {
    int n = fruits.size();
    std::unordered_map<int,int> freq;
    int left = 0;
    int right;
    int best = 0;
    for(right = 0;right<n;right++){
        freq[fruits[right]]++;
        while (freq.size() > 2) {
            int old = fruits[left];
            --freq[old];

         if (freq[old] == 0) {
            freq.erase(old);
        }

        ++left;
        }
        int length =right - left +1;
        if(length > best){
            best =length;
        }
    }
    return best;
}

int main() {
    struct Case {
        std::vector<int> fruits;
        int expected;
    };
    const std::vector<Case> cases = {
        {{1, 2, 1}, 3},
        {{0, 1, 2, 2}, 3},
        {{1, 2, 3, 2, 2}, 4},
        {{3, 3, 3}, 3},
        {{}, 0},
        {{1, 2, 1, 2, 3, 3, 2, 2}, 5},
    };

    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        int actual = totalFruit(cases[i].fruits);
        if (actual == cases[i].expected) {
            ++passed;
        } else {
            std::cout << "case " << i + 1 << ": expected " << cases[i].expected
                      << ", got " << actual << '\n';
        }
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
}
