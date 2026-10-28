#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// 题目：返回出现频率最高的 k 个不同数字。
// 结果按频率从高到低排列；频率相同时，数字从小到大排列。
// 空输入或 k <= 0：返回空数组。
// k 超过不同数字的数量：返回全部不同数字，仍按上述规则排序。
// 本次先自己重写排序版；可以询问语法，提示会如实记录。
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    // 在这里实现；写好后删除下面三行占位代码。
    std::unordered_map<int,int> cnt;
    for(int x :nums){
        cnt[x]++;
    }
    if( k <= 0){
        return {};
    }
    int n = cnt.size();
    std::vector<std::pair<int,int>> sort1;
    for(const auto& item : cnt){
        sort1.push_back(item);
    }
    std::sort(sort1.begin(),sort1.end(),
        [](const auto& a, const auto& b){
            if(a.second != b.second)
            return a.second > b.second;
            return a.first < b.first;
        });
    std::vector<int> result;
    if(k>n){
        k = n;
    }
    for(int i = 0;i <k; i++){
        result.push_back(sort1[i].first);
    }
    return result;
}

// 以下是测试区，不需要修改。
int main() {
    struct Case {
        std::vector<int> nums;
        int k;
        std::vector<int> expected;
    };
    const std::vector<Case> cases{
        {{12, 7, 12, 3, 7, 12, 3, 8}, 2, {12, 3}},
        {{}, 2, {}},
        {{9, 9, 2}, 0, {}},
        {{9, 9, 2}, -2, {}},
        {{6, 2, 6, 4}, 9, {6, 2, 4}},
        {{-4, 8, -4, 8, 2}, 2, {-4, 8}},
        {{11, 5, 9}, 2, {5, 9}},
        {{7, 7, 7}, 1, {7}}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        try {
            const auto actual = topKFrequent(cases[i].nums, cases[i].k);
            const bool ok = actual == cases[i].expected;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL") << '\n';
            if (ok) {
                ++passed;
            } else {
                std::cout << "actual:";
                for (int x : actual) std::cout << ' ' << x;
                std::cout << "\nexpected:";
                for (int x : cases[i].expected) std::cout << ' ' << x;
                std::cout << '\n';
            }
        } catch (const std::exception& e) {
            std::cout << "case " << i + 1 << ": " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
