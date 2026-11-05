#include <iostream>
#include <vector>

// nums 严格升序；返回 target 下标，找不到返回 -1。
int binarySearch(const std::vector<int>& nums, int target) {
    // 独立实现。
    int n = nums.size();
    int left = 0;
    int right = n-1;
    int mid = 0;
    while(left <=right){
        mid = left + (right- left)/2;
        if(nums[mid] < target){
            left = mid +1;
        }
        else if(nums[mid] > target){
            right = mid -1;
        }else{
            return mid;
        }
    }
    return -1;
}

void check(const char* name, int actual, int expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", binarySearch({}, 3), -1);
    check("first", binarySearch({1, 3, 5, 7, 9}, 1), 0);
    check("middle", binarySearch({1, 3, 5, 7, 9}, 5), 2);
    check("last", binarySearch({1, 3, 5, 7, 9}, 9), 4);
    check("missing", binarySearch({1, 3, 5, 7, 9}, 6), -1);
    check("single", binarySearch({4}, 4), 0);
}
