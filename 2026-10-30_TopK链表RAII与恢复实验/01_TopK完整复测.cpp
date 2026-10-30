#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// 返回出现次数最多的前k个不同数字。
// 频率降序；同频时数字升序。
// k<=0返回空；k超种类数返回全部，顺序仍遵循上面的规则。
// 示例：{14,5,14,2,5,14,2,9}，k=2，返回{14,2}。
// 今天先尝试完整写出排序版，提交后直接审查整段。
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    // 你的实现：计数、pair数组、排序、边界及取结果。
    std::unordered_map<int,int> cnt;
    for(int x : nums){
        cnt[x]++;
    }
    if(k <= 0){
        return {};
    }
    std::vector<std::pair<int,int>> pair;
    for(const auto& item : cnt){
        pair.push_back(item);
    }
    std::sort(pair.begin(),pair.end(),
        [] (const auto& a,const auto&b){
            if(a.second != b.second){
                return a.second > b.second;
            }
            return a.first < b.first;
        });
    std::vector<int> result;
    int n = cnt.size();
    if(k > n){
        k = n;
    }
    for(int i =0;i<k;i++){
        result.push_back(pair[i].first);
    }
    return result;
}

// 以下测试区不需要修改。
int main() {
    struct Case {
        std::vector<int> nums;
        int k;
        std::vector<int> expected;
    };
    const std::vector<Case> cases{
        {{14, 5, 14, 2, 5, 14, 2, 9}, 2, {14, 2}},
        {{}, 3, {}},
        {{6, 6, 1}, 0, {}},
        {{6, 6, 1}, -3, {}},
        {{-6, 8, -6, 3}, 10, {-6, 3, 8}},
        {{11, 4, 7}, 2, {4, 7}},
        {{9, 9, 9}, 1, {9}},
        {{5, -2, 5, -2, 8}, 2, {-2, 5}}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        try {
            const auto actual = topKFrequent(cases[i].nums, cases[i].k);
            const bool ok = actual == cases[i].expected;
            if (ok) ++passed;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL") << '\n';
            if (!ok) {
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
