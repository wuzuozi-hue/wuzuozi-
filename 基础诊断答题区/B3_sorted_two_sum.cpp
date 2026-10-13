// B3 练习：在升序数组中找两个数，使它们的和等于 target。
// 返回两个下标；找不到则返回 {}。
// 例如 {1, 4, 6, 9, 13}，target = 15，答案是 {2, 3}。

#include <iostream>
#include <vector>

std::vector<int> twoSumSorted(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left < right) {
        int sum = nums[left] + nums[right];

        if (sum == target) {
            return {left, right};
        }

        if (sum < target) {
            // TODO 1：和太小，应该移动哪一个下标？
            left++;
             // 占位：写出移动语句后删掉这行
        } else {
            // TODO 2：和太大，应该移动哪一个下标？
            --right;
             // 占位：写出移动语句后删掉这行
        }
    }

    return {};
}

int main() {
    int passed = 0;
    if (twoSumSorted({1, 4, 6, 9, 13}, 15) == std::vector<int>({2, 3})) ++passed;
    if (twoSumSorted({2, 5, 8}, 7) == std::vector<int>({0, 1})) ++passed;
    if (twoSumSorted({1, 3, 5}, 20) == std::vector<int>({})) ++passed;

    std::cout << "通过 " << passed << "/3 个用例\n";
}
