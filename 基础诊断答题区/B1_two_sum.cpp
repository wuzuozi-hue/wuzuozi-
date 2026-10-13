// B1：两数之和（第一版先用两层循环）
// 给定整数数组 nums 和目标 target，返回两个不同下标，
// 使 nums[下标1] + nums[下标2] == target。
// 没有答案时返回空数组 {}。
// 例子：nums = {3, 3}, target = 6，应返回 {0, 1}。
//
// 你只需要填写 twoSum 函数。先独立尝试，不要看参考答案。
// 提示：第二层循环从 i + 1 开始，就不会重复使用同一个元素。

#include <iostream>
#include <vector>

std::vector<int> twoSum(std::vector<int> nums, int target) {
    // 在这里写两层 for 循环；找到时返回 {i, j}。
    // 没找到时保留下面这一句。
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
