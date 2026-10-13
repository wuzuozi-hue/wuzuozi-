// B1 两数之和：哈希表版本
// 只补两处 TODO；顺序必须是“先查之前的数字，再记录当前数字”。

#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int> nums, int target) {
    std::unordered_map<int, int> seen;  // 数字 -> 之前出现的下标
    int n = static_cast<int>(nums.size());

    for (int i = 0; i < n; ++i) {
        int current = nums[i];
        int need = target - current;

        // TODO 1：如果 seen 里有 need，返回 {之前的下标, i}。

        // TODO 2：否则记录 current 出现在下标 i。
    }

    return {};
}

int main() {
    int passed = 0;
    if (twoSum({3, 3}, 6) == std::vector<int>({0, 1})) {
        ++passed;
    } else {
        std::cout << "重复值用例未通过\n";
    }

    if (twoSum({}, 6).empty()) {
        ++passed;
    } else {
        std::cout << "空数组用例未通过\n";
    }

    if (twoSum({-2, 7, 3}, 1) == std::vector<int>({0, 2})) {
        ++passed;
    } else {
        std::cout << "负数用例未通过\n";
    }

    if (twoSum({1, 2}, 9).empty()) {
        ++passed;
    } else {
        std::cout << "无解用例未通过\n";
    }

    std::cout << "通过 " << passed << "/4 个用例\n";
    return passed == 4 ? 0 : 1;
}
