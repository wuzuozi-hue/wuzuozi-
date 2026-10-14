#include <iostream>
#include <unordered_map>
#include <vector>

// 题目：和为 K 的连续子数组
//
// 给定一个整数数组 nums 和整数 k，返回和等于 k 的连续子数组个数。
// 子数组必须连续，长度至少为 1。
// 数组中可能包含负数、0 和正数。
//
// 示例：
// nums = {1, 1, 1}, k = 2  -> 2
// nums = {1, 2, 3}, k = 3  -> 2
// nums = {1, -1, 0}, k = 0 -> 3
//
// 要求：
// 1. 先完成能通过测试的算法。
// 2. 再写出时间复杂度和空间复杂度。
// 3. 不要修改 main 中的测试。
//
// 提示：连续子数组可以用“前缀和”描述；先自己推导需要记录什么。
int subarraySum(const std::vector<int>& nums, int k) {
    // TODO：在这里实现。
    int n = nums.size();
    int count = 0;
    for(int i = 0; i<n;i++){
        int sum = 0;
        for(int j=i;j<n;j++){
            sum = sum + nums[j];
            if(sum == k)
            count++;
        }
    }
    return count;
}

void check(const std::vector<int>& nums, int k, int expected) {
    const int actual = subarraySum(nums, k);
    std::cout << (actual == expected ? "PASS" : "FAIL")
              << " | expected=" << expected
              << " actual=" << actual << '\n';
}

int main() {
    check({1, 1, 1}, 2, 2);
    check({1, 2, 3}, 3, 2);
    check({1, -1, 0}, 0, 3);
    check({3, 4, 7, 2, -3, 1, 4, 2}, 7, 4);
    return 0;
}
