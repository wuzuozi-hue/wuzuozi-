// B2 练习：找第一个重复的数字
// 从左到右扫描，遇到重复时返回 {第一次出现的下标, 当前下标}。
// 例如 {8, 4, 6, 4, 8} 返回 {1, 3}；没有重复则返回 {}。

#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> firstDuplicate(const std::vector<int>& nums) {
    std::unordered_map<int, int> seen; // 数字 -> 第一次出现的下标

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        int current = nums[i];

        // TODO 1：如果 current 已经在 seen 中，返回两个下标。
        if(seen.count(current)> 0)
        {
            return {seen[current],i};
        }
        // seen 8 = 0 seen 4 = 1 seen 6 = 2 seen 4 = 3
        seen[current] = i;
        // TODO 2：否则记录 current 第一次出现的下标。

    }

    return {};
}

int main() {
    int passed = 0;
    if (firstDuplicate({8, 4, 6, 4, 8}) == std::vector<int>({1, 3})) ++passed;
    if (firstDuplicate({5, 2, 9}) == std::vector<int>({})) ++passed;
    if (firstDuplicate({-1, 7, -1}) == std::vector<int>({0, 2})) ++passed;

    std::cout << "通过 " << passed << "/3 个用例\n";
}
