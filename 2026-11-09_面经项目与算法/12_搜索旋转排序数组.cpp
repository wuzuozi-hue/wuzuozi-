#include <iostream>
#include <vector>

// LeetCode 33（Mid，复测）
// 原数组严格升序、无重复值，可能在某个位置旋转，也可能没有旋转。
// 找到 target 返回下标；不存在返回 -1。要求 O(log n) 时间。
// 如 [0,1,2,4,5,6,7] 旋转得到 [4,5,6,7,0,1,2]。
// target=0 返回 4；target=3 返回 -1。空数组返回 -1。
//0, 1, 2, 4, 5, 6, 7
//7  0  1  2  4  5  6
int search(const std::vector<int>& nums, int target) {
    if(nums.empty())
    return -1;
    int n = nums.size();
    int left = 0;
    int right = n-1;
    while(left <= right){
        int mid = left +(right - left)/2;
        if(nums[mid] == target){
            return mid;
        }
        if(nums[left] <= nums[mid]){
            if(nums[left] <=target && nums[mid] >target){
                right = mid-1;
            }else{
                left = mid+1;
            }
        }
        else{
            if(nums[mid] <target && target <= nums[right]){
                left = mid +1;
            }else{
                right = mid -1;
            }
        }
    }
    return -1;
}

int main() {
    int failed = 0;
    auto check = [&](const char* name, std::vector<int> nums, int target, int expected) {
        int actual = search(nums, target);
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << " actual=" << actual << '\n';
        if (!ok) ++failed;
    };
    check("rotated hit", {4,5,6,7,0,1,2}, 0, 4);
    check("rotated missing", {4,5,6,7,0,1,2}, 3, -1);
    check("empty", {}, 1, -1);
    check("single hit", {1}, 1, 0);
    check("single missing", {1}, 0, -1);
    check("two rotated", {3,1}, 1, 1);
    check("no rotation", {1,2,3,4,5}, 4, 3);
    check("left boundary", {6,7,1,2,3,4,5}, 6, 0);
    check("right boundary", {6,7,1,2,3,4,5}, 5, 6);
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
