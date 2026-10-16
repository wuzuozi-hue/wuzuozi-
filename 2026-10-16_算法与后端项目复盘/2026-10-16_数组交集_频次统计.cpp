#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

// 在用户 2026-10-16 的作答基础上，仅修正 find 那一行的语法。
std::vector<int> intersect(const std::vector<int>& first,
                           const std::vector<int>& second) {
    std::unordered_map<int, int> cnt;
    for (int x : first) {
        ++cnt[x];
    }

    std::vector<int> result;
    for (int y : second) {
        auto it = cnt.find(y);
        if (it != cnt.end() && it->second > 0) {
            result.push_back(y);
            --it->second;
        }
    }
    return result;
}

int main() {
    struct Case {
        std::vector<int> a;
        std::vector<int> b;
        std::vector<int> expected;
    };
    const std::vector<Case> cases{
        {{1, 2, 2, 1}, {2, 2}, {2, 2}},
        {{4, 9, 5}, {9, 4, 9, 8, 4}, {4, 9}},
        {{}, {1, 2}, {}},
        {{1, 1, 2}, {1, 2, 2}, {1, 2}},
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        auto got = intersect(cases[i].a, cases[i].b);
        auto want = cases[i].expected;
        std::sort(got.begin(), got.end());
        std::sort(want.begin(), want.end());
        const bool ok = got == want;
        passed += ok;
        std::cout << "case " << i + 1 << (ok ? " PASS" : " FAIL") << '\n';
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
}
