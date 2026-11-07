// 2026-11-07 | LeetCode 33 | 中等 | 复测 | 状态：未开始
// 题意：一个严格升序、元素互异的数组经过一次旋转（也可能未旋转），查找 target。
// 输入：非空数组 nums、target。输出：目标下标，不存在返回 -1。
// 本地扩展防御约定：空数组返回 -1（超出原题非空约束）。
// 要求：时间复杂度 O(log n)。边界：单元素、未旋转、目标在旋转点两侧。
// 只替换 TODO；通过这些功能测试后，还要口述复杂度，不能仅靠样例声称 O(log n)。
#include <iostream>
#include <vector>

int search(const std::vector<int>& nums, int target) {
    int n = nums.size();
    if( n == 0){
        return -1;
    }
    int left =0;
    int right = n-1;
    while(left<= right){
        int mid = left +(right -left)/2;
        if(nums[mid] == target){
            return mid;
        }
        if(nums[left] <=nums[mid]){
            if(nums[left] <= target && target <nums[mid]){
                right =mid -1;
            }else{
                left = mid+1;
            }
        }
        else{
            if(nums[right] >= target && target >nums[mid]){
                left =mid +1;
            }else{
                right = mid -1;
            }
        }

    }
    return -1;
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, const std::vector<int>& nums, int target, int expected) {
        int actual = search(nums, target);
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL")
                  << " (actual=" << actual << ", expected=" << expected << ")\n";
        failures += !ok;
    };
    check("empty", {}, 2, -1);
    check("single found", {1}, 1, 0);
    check("not rotated", {-3, 0, 4, 9}, 9, 3);
    check("before pivot", {4, 5, 6, 7, 0, 1, 2}, 6, 2);
    check("at pivot", {4, 5, 6, 7, 0, 1, 2}, 0, 4);
    check("missing in rotated array", {3, 1}, 2, -1);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
