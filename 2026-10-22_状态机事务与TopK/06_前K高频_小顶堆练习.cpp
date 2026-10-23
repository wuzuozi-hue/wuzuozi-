// 2026-10-22：把前 K 个高频元素从“全排序”改为“容量为 K 的小顶堆”。
// 本练习样例无频率并列；并列时的确定性次序留到下一阶段讨论。
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

std::vector<int> topKFrequentHeap(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> freq;
    for (int value : nums) ++freq[value];

    using Candidate = std::pair<int, int>; // {次数, 数字}
    std::priority_queue<Candidate, std::vector<Candidate>, std::greater<Candidate>> heap;

    for (const auto& item : freq) {
        // item.first 是数字；item.second 是次数。

        // TODO 1：把 {次数, 数字} 放入 heap。
        heap.push({item.second,item.first});
        // TODO 2：如果堆中元素多于 k 个，弹出最弱候选。
        if(heap.size() > k){
            heap.pop();
        }
    }

    std::vector<int> result;
    while (!heap.empty()) {
        result.push_back(heap.top().second);
        heap.pop();
        // TODO 3：把堆顶候选中的“数字”加入 result，然后弹出堆顶。
         // 实现 TODO 3 后删掉这行
    }
    std::sort(result.begin(), result.end()); // 测试只比较结果集合
    return result;
}

int main() {
    struct Case { std::vector<int> nums; int k; std::vector<int> expected; };
    const Case cases[] = {
        {{1, 1, 1, 2, 2, 3}, 2, {1, 2}},
        {{5, 5, 5, 5, 6, 6, 7}, 1, {5}},
        {{-3, -3, -3, 8, 8, 2}, 2, {-3, 8}},
    };
    int passed = 0;
    for (const auto& test : cases) {
        if (topKFrequentHeap(test.nums, test.k) == test.expected) ++passed;
    }
    std::cout << passed << "/" << (sizeof(cases) / sizeof(cases[0])) << " passed\n";
    return passed == static_cast<int>(sizeof(cases) / sizeof(cases[0])) ? 0 : 1;
}
