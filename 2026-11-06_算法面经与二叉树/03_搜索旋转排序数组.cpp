#include <iostream>
#include <vector>

// nums 原本严格递增，在某个位置旋转，元素互不相同。
// 返回 target 的下标；找不到返回 -1。尝试 O(log n) 时间。
int search(const std::vector<int>& nums, int target) {
    int n = nums.size();
    int left = 0;
    int right = n-1;
    while(left <= right){
        int mid = left +(right -left)/2;
        if(nums[mid] == target){
            return mid;
        }
        if(nums[left] <= nums[mid]){
            if(nums[left] <=target && target <nums[mid]){
                right = mid -1;
            }
            else{
                left = mid +1;
            }
        }else{
            if(nums[mid] < target && target <=nums[right]){
                left = mid +1;
            }else{
                right = mid-1;
            }
        }
    }
    return -1;
}

void check(const char* name, const std::vector<int>& nums, int target, int expected) {
    std::cout << name << ": " << (search(nums, target) == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("rotated", {4, 5, 6, 7, 0, 1, 2}, 0, 4);
    check("missing", {4, 5, 6, 7, 0, 1, 2}, 3, -1);
    check("sorted", {1, 2, 3, 4, 5}, 4, 3);
    check("single", {1}, 1, 0);
    check("empty", {}, 5, -1);
    check("rotated once", {7, 1, 2, 3, 4, 5, 6}, 7, 0);
}
