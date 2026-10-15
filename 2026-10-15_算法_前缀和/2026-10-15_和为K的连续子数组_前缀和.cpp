#include <iostream>
#include <unordered_map>
#include <vector>

// 第一步：返回 {0, 第 1 个数之和, 前 2 个数之和, ...}。
// 例：{2, -1, 3} -> {0, 2, 1, 4}。
std::vector<long long> buildPrefix(const std::vector<int>& nums) {
    // prefix[0] 表示空前缀，之后依次记录前 1、2、... 个数的和。
    int n = nums.size();
    long long sum = 0;
    std::vector<long long> prefix{0};
    for(int i = 0; i<n;i++){
        sum += nums[i];
        prefix.push_back(sum);
    }
    return prefix;
}
// 第二步：统计和恰好为 k 的连续、非空子数组个数。
// 与昨天的双重循环版本比较：思考“当前前缀 - 哪个旧前缀 = k”。
int subarraySumFast(const std::vector<int>& nums, int k) {

    // 旧前缀和 -> 此前出现次数。
    std::unordered_map<long long, int> prefixcount;
    int n = nums.size();
    long long pref = 0;
    int  count = 0;
    // 空前缀出现一次，才能统计从下标 0 开始的区间。
    prefixcount[0] = 1;
    for(int i = 0; i <n; i++){
        pref += nums[i];//表示前缀和
        long long need = pref - k;
        auto it = prefixcount.find(need);
        if(it != prefixcount.end()){
            count += it->second;
        }
        ++prefixcount[pref];

    }
    // 先查旧前缀、后记录当前前缀，避免把空区间算进去。
    return count;
}

int main() {
    const bool prefixOk = buildPrefix({2, -1, 3}) == std::vector<long long>{0, 2, 1, 4}
                       && buildPrefix({}) == std::vector<long long>{0};
    std::cout << "prefix " << (prefixOk ? "PASS" : "FAIL") << '\n';

    struct Case { std::vector<int> nums; int k; int expected; };
    const std::vector<Case> cases{
        {{1, 1, 1}, 2, 2},
        {{1, 2, 3}, 3, 2},
        {{1, -1, 0}, 0, 3},
        {{3, 4, 7, 2, -3, 1, 4, 2}, 7, 4},
        {{0, 0}, 0, 3},
        {{}, 5, 0},
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
