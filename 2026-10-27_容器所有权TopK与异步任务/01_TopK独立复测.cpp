#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// 返回频率最高的 k 个不同数字：频率降序，同频按数值升序。
// k <= 0 返回空；k 大于不同数字数时返回全部。
// 仅要求排序版；写下思路后独立实现。空 vector 不能直接 result[i] 写入。
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map <int,int> cnt;
    for(int x : nums){
        cnt[x]++;
    }
    std::vector<std::pair<int,int>> pairs;
    for(const auto& item : cnt){
        pairs.push_back(item);
    }
    std::sort(pairs.begin(),pairs.end(),
    [](const auto& a,const auto&b){
            if(a.second!= b.second){
                return a.second>b.second;
            }
            return a.first<b.first;
    });
    std::vector<int> result;
    if(k<=0)
    return {};
    int kinds = static_cast<int>(pairs.size());
    if(k > kinds){
        k = kinds;
    }
    for(int i =0;i<k;i++){

        result.push_back(pairs[i].first);

    }
    return result;
}

int main() {
    struct Case { std::vector<int> nums; int k; std::vector<int> expected; };
    const std::vector<Case> cases{
        {{}, 2, {}}, {{4, 4}, 0, {}}, {{2, 2, 1}, 5, {2, 1}},
        {{-3, -3, 7, 7, 8}, 2, {-3, 7}}, {{5, 6, 7}, 2, {5, 6}},
        {{4, 4, 4}, 1, {4}}, {{1, 1, 1, 2, 2, 3}, 2, {1, 2}},
        {{8, 8, 4}, -1, {}}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        try {
            const auto actual = topKFrequent(cases[i].nums, cases[i].k);
            const bool ok = actual == cases[i].expected;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL") << '\n';
            if (ok) ++passed;
            else {
                std::cout << "actual:";
                for (int x : actual) std::cout << ' ' << x;
                std::cout << "\nexpected:";
                for (int x : cases[i].expected) std::cout << ' ' << x;
                std::cout << '\n';
            }
        } catch (const std::exception& e) {
            std::cout << "case " << i + 1 << ": NOT COMPLETED - " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
