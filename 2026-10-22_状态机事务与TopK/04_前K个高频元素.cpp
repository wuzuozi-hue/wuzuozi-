// 2026-10-22：前 K 个高频元素。先做哈希表计数，再决定如何取前 K 个。
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> topKFrequent(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> freq; // 数字 -> 出现次数

    // TODO 1：遍历 nums，统计每个数字出现的次数。
    for(int x :nums){
        freq[x]++;
    }
    // TODO 2：把 freq 的“数字、次数”复制到下面的 pairs。
    std::vector<std::pair<int, int>> pairs;
    for(const auto& item :freq){
        pairs.push_back(item);
    }
    // TODO 3：按次数从大到小排序；次数相同时数字从小到大。
    std::sort(pairs.begin(),pairs.end(),[](const auto&a,const auto& b){
        if(a.second != b.second){
            return a.second>b.second;
        }
        return a.first < b.first;
    });
    // TODO 4：取前 k 个数字，放入 result。
    std::vector<int> result;
    for(int i = 0;i<k;i++){
        result.push_back(pairs[i].first);
    }

    return result;
}

int main() {
    struct Case { std::vector<int> nums; int k; std::vector<int> expected; };
    const Case cases[] = {
        {{1, 1, 1, 2, 2, 3}, 2, {1, 2}},
        {{4, 4, 2, 3, 3, 3}, 1, {3}},
        {{-2, -2, 5, 5, 7}, 2, {-2, 5}},
        {{5,6,7}, 2, {5,6}},
    };
    int passed = 0;
    for (const auto& test : cases) {
        if (topKFrequent(test.nums, test.k) == test.expected) ++passed;
    }
    std::cout << passed << "/" << (sizeof(cases) / sizeof(cases[0])) << " passed\n";
    return passed == static_cast<int>(sizeof(cases) / sizeof(cases[0])) ? 0 : 1;
}
