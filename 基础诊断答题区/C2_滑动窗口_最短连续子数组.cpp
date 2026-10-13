// C2：滑动窗口优化
//
// 给定正整数 target 和只包含正整数的 nums，返回总和 >= target
// 的连续子数组的最短长度；不存在则返回 0。
//
// 例：target = 7, nums = {2, 3, 1, 2, 4, 3}
// 答案为 2，对应连续子数组 {4, 3}。
//
// 上一题的双层循环是 O(n^2)。本题要求使用滑动窗口，目标是 O(n)。
// 请自己补全函数，并说明：
// 1. right 每次向右扩展时做什么？
// 2. 窗口总和达到 target 后，为什么可以移动 left？
// 3. 时间复杂度为什么是 O(n)？

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int minSubArrayLenSliding(int target, const std::vector<int>& nums) {
    int left = 0;
    int sum = 0;
    int best = std::numeric_limits<int>::max();

    for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
        // TODO 1：把 nums[right] 加入当前窗口。
        sum += nums[right];
        while (sum >= target) {
            // TODO 2：用当前窗口长度更新 best。
            best = std::min(best,right-left+1);
            // TODO 3：移除 nums[left]，并让 left 向右移动一格。
            sum = sum - nums[left];
            left++;
        }
    }

    // TODO 4：没有找到有效窗口时返回 0，否则返回 best。
    if(best == std::numeric_limits<int>::max()){
        return 0;
    }
    return best;
}

int main() {
    int passed = 0;

    if (minSubArrayLenSliding(7, {2, 3, 1, 2, 4, 3}) == 2) ++passed;
    if (minSubArrayLenSliding(4, {1, 4, 4}) == 1) ++passed;
    if (minSubArrayLenSliding(6, {1, 1, 1, 1}) == 0) ++passed;
    if (minSubArrayLenSliding(5, {5}) == 1) ++passed;
    if (minSubArrayLenSliding(8, {4, 1, 4}) == 3) ++passed;
    if (minSubArrayLenSliding(15, {5, 5, 5, 5}) == 3) ++passed;

    std::cout << "通过 " << passed << "/6 个用例\n";
}
