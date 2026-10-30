#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// 返回出现次数最多的前k个不同数字：频率降序，同频数字升序。
// k<=0或输入为空返回空；k超种类数时返回全部不同数字。
// 示例：{3,10,3,4,10,3,4,8}，k=2，返回{3,4}。
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int,int> cnt;
    for(int x :nums){
        cnt[x]++;
    }
    int n = cnt.size();
    if(k<=0){
        return {};
    }
    std::vector<std::pair<int,int>> pair;
    for(const auto& item : cnt){
        pair.push_back(item);
    }
    std::sort(pair.begin(),pair.end(),
        [](const auto&a,const auto& b){
            if(a.second != b.second){
                return a.second > b.second;
            }
            return a.first < b.first;
        });
    std::vector<int> result;

    if(k > n){
        k = n;
    }
    for(int i =0;i<k; i++){
        result.push_back(pair[i].first);
    }
    return result;
}

// 测试区无需修改。
int main() {
    struct Case { std::vector<int> nums; int k; std::vector<int> expected; };
    const std::vector<Case> cases{
        {{3, 10, 3, 4, 10, 3, 4, 8}, 2, {3, 4}},
        {{}, 2, {}},
        {{5, 5, 1}, 0, {}},
        {{5, 5, 1}, -2, {}},
        {{-7, 6, -7, 2}, 8, {-7, 2, 6}},
        {{12, 3, 8}, 2, {3, 8}},
        {{4, 4, 4}, 1, {4}},
        {{5, -4, 5, -4, 9}, 2, {-4, 5}}
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
