#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

// 题目：返回频率最高的k个不同数字。
// 频率高的排前面；同频时数字小的排前面。
// k<=0返回空；k超种类数返回全部，仍按上述规则排序。
// 数据示例：{10,4,10,6,4,10,6,8}，k=3，结果为{10,4,6}。
// 今天逐段写，先只完成第1步；最终完成全部步骤后再运行测试。
std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    // 第1步：用哈希表cnt，统计“数字 -> 出现次数”。
    std::unordered_map<int,int> cnt;
    for(int x : nums){
        cnt[x]++;
    }
    // 第2步：把哈希表元素放入pair数组，保留数字和次数。
    std::vector<std::pair<int,int>> pair;
    int n = cnt.size();
    if(k<= 0){
        return {};
    }
    for(const auto& item :cnt){
        pair.push_back(item);
    }
    // 第3步：写排序比较器，先按次数降序，再按数字升序。
    std::sort(pair.begin(),pair.end(),
        [] (const auto& a,const auto& b){
            if(a.second != b.second){
                return a.second>b.second;
            }
            return a.first < b.first;
        });
    std::vector<int> result;
    if(k>n){
        k = n;
    }
    for(int i =0;i<k;i++){
        result.push_back(pair[i].first);
    }
    // 第4步：处理k边界，取出前k个数字并返回。
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
        {{10, 4, 10, 6, 4, 10, 6, 8}, 3, {10, 4, 6}},
        {{}, 2, {}},
        {{7, 7, 3}, 0, {}},
        {{7, 7, 3}, -1, {}},
        {{-2, 9, -2, 5}, 10, {-2, 5, 9}},
        {{9, 3, 6}, 2, {3, 6}},
        {{8, 8, 8}, 1, {8}},
        {{5, 5, -3, -3, 2}, 2, {-3, 5}}
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
