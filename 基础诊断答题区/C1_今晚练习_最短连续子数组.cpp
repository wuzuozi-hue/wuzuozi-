晚算法练习：长度最短的连续子数组
//
// 给定一个正整数 target，以及一个只包含正整数的数组 nums。
// 找出总和 >= target 的连续子数组中的最短长度。
// 如果不存在，返回 0。
//
// 示例：
// target = 7, nums = {2, 3, 1, 2, 4, 3}
// 答案是 2，因为连续子数组 {4, 3} 的总和是 7。
//
// 今晚第一阶段：只写双层循环版本，不排序，不优化。
// 要求：完成后说出时间复杂度，并解释一个边界情况。

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

int minSubArrayLen(int target, const std::vector<int>& nums) {
    int n = static_cast<int>(nums.size());
    int best = std::numeric_limits<int>::max();

   or (int i = 0; i < n; ++i) {
        int sum = 0;

            sum += nums[j];

            if (sum >= target) {
                int length = j - i + 1;
                best = std::min(best, length); 

                // TODO：用 length 更新 best。
                // 提示：best 应该保留更小的那个长度。

                break;
            
            }        }
    }

    // TODO：如果 best 仍然没有被更新，返回 0；否则返回 best。
    if(best == std::numeric_limits<int>::max()){
        return ;
    }
    return best;
}
int main() {
    int passed = 0

    if (minSubArrayLen(7, {2, 3, 1, 2, 4, 3}) == 2) ++passed;
    if (minSubArrayLen(4, {1, 4, 4}) == 1) ++passed;
    if (minSubArrayLen(6, {1, 1, 1, 1}) == 0) ++passed;
    if (minSubArrayLen(5, {5}) == 1) ++passed;
    if (minSubArrayLen(11, {}) == 0) ++passed;
    if (minSubArrayLen(8, {4, 1, 4}) == 3) ++passed;

    std::cout << "通过 " << passed << "/6 个用例\n";