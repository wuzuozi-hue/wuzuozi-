#include <iostream>
#include <vector>

// nums 严格升序；找到目标返回下标，否则返回保持升序的插入位置。
int searchInsert(const std::vector<int>& nums, int target) {
    int n = nums.size();
    int left = 0;
    int right = n-1;
    int mid = 0;
    while(left <= right){
        mid = left + (right - left) / 2;
        if(nums[mid] == target){
            return mid;
        }else if( nums[mid] < target){
             left = mid +1;
        }else{
             right = mid -1;
        }
    }
    return left;
}

void check(const char* name, int actual, int expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", searchInsert({}, 3), 0);
    check("found", searchInsert({1, 3, 5, 6}, 5), 2);
    check("middle insert", searchInsert({1, 3, 5, 6}, 2), 1);
    check("end insert", searchInsert({1, 3, 5, 6}, 7), 4);
    check("start insert", searchInsert({1, 3, 5, 6}, 0), 0);
    check("single insert", searchInsert({4}, 3), 0);
}
