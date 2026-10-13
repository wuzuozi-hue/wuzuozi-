// 水平复评：长度最短的连续子数组
// 给定一个正整数 target 和一个只含正整数的数组 nums。
// 找出总和 >= target 的连续子数组中，最短的长度；不存在则返回 0。
// 例如 target=7, nums={2,3,1,2,4,3}，答案是 2，因为 {4,3}。
//
// 请独立完成函数，不限制解法。完成后说出时间复杂度，并解释一个边界情况。

#include <iostream>
#include <vector>
#include <algorithm>
int minSubArrayLen(int target, const std::vector<int>& nums) {
    // 在这里独立实现。
    int n = nums.size();
    for (int i = 0; i < n; ++i) {       // i：这次从哪里开始
    int sum = 0;                    // 换起点时，重新累计
    for (int j = i; j < n; ++j) {   // j：这次延伸到哪里
        sum += nums[j];             // 当前连续范围是 nums[i] 到 nums[j]

        if (sum >= target) {
            int length = j - i + 1;
            // 用 length 更新目前找到的最短长度
            break;
        }
    }
}
    // std::sort(nums.begin(),nums.end());
    // int sum = 0;
    // for(int i = 0;i<n;i++){
    //     sum = sum+nums[i];
    // }
    // if(sum < target){
    //     return 0;
    // }
    
    // if(nums[n-1] > target)
    // return 1;
    // sum = 0;
    // for(int i = n; i>0;i--){
    //     int count = 1;
    //     sum = sum + nums[i];
    //     if(sum >target){
    //         return count;
    //     }
    //     count++;
    // }
   
    // return 0;
}

int main() {
    int passed = 0;
    if (minSubArrayLen(7, {2, 3, 1, 2, 4, 3}) == 2) ++passed;
    if (minSubArrayLen(4, {1, 4, 4}) == 1) ++passed;
    if (minSubArrayLen(6, {1, 1, 1, 1}) == 0) ++passed;
    if (minSubArrayLen(5, {5}) == 1) ++passed;
    if (minSubArrayLen(11, {}) == 0) ++passed;

    std::cout << "通过 " << passed << "/5 个用例\n";
}
