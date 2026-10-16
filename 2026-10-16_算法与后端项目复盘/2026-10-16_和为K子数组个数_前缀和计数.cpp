#include <iostream>
#include <unordered_map>
#include <vector>

// 2026-10-16 独立复写：统计和为 k 的连续、非空子数组个数。
// 先不看昨天的答案；写出自己的变量含义和查找/记录顺序。
int subarraySumFast(const std::vector<int>& nums, int k) {
    // 在这里独立实现。可以在纸上先推 {5, -2, 4, -2}, k=2。
    std::unordered_map<long long ,int>prefixcount;
    prefixcount[0] = 1;
    int count = 0;
    int n = nums.size();
    long long prefix = 0;
    for(int i = 0; i<n; i++){
        prefix +=nums[i];
        long long  need = prefix -k;
        auto it = prefixcount.find(need);
        if(it != prefixcount.end()){
            count += it->second;
        }
        ++prefixcount[prefix];
    }
    return count; // 占位；写完后删除。
}

int main() {
    struct Case { std::vector<int> nums; int k; int expected; };
    const std::vector<Case> cases{
        {{5, -2, 4, -2}, 2, 2},
        {{1, -1, 0}, 0, 3},
        {{0, 0, 0}, 0, 6},
        {{}, 7, 0},
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const int got = subarraySumFast(cases[i].nums, cases[i].k);
        const bool ok = got == cases[i].expected;
        passed += ok;
        std::cout << "case " << i + 1 << (ok ? " PASS" : " FAIL")
                  << " (got " << got << ", expected " << cases[i].expected << ")\n";
    }
    std::cout << "passed " << passed << '/' << cases.size() << '\n';
}
