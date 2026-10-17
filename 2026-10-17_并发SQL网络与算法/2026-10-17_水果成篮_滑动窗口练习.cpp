// 2026-10-17 算法收尾：水果成篮（LeetCode 904）
//
// 给定水果类型数组，找出只包含至多 2 种类型的最长连续子数组长度。
// 例如 {1, 2, 3, 2, 2} -> 4，对应 {2, 3, 2, 2}。
// 要求：滑动窗口，目标时间复杂度 O(n)。先自己写，再运行测试。

#include <iostream>
#include <unordered_map>
#include <vector>

int totalFruit(const std::vector<int>& fruits) {
    // TODO 1：定义窗口左边界、最长长度和“水果类型 -> 窗口内次数”。
    // TODO 2：右边界逐个加入水果。
    // TODO 3：如果窗口中超过 2 种类型，从左边缩小窗口。
    // TODO 4：每轮更新最长长度。
    (void)fruits;
    return -1; // 占位：实现后替换。
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
