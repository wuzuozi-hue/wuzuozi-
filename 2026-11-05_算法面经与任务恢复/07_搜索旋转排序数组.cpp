#include <iostream>
#include <vector>

// nums 是严格升序数组旋转后的结果，元素互不相同；找不到返回 -1。
int searchRotated(const std::vector<int>& nums, int target) {
    // 在这里实现。
    int n = nums.size();
    int left = 0;
    int right = n -1;
    while(left <= right){
        if(nums[left] ==  target){
            return left;
        }
        if(nums[right] == target){
            return right;
        }
        ++left;
        --right;
    }
    return -1;
}

void check(const char* name, int actual, int expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", searchRotated({}, 3), -1);
    check("rotated left", searchRotated({4, 5, 6, 7, 0, 1, 2}, 5), 1);
    check("rotated right", searchRotated({4, 5, 6, 7, 0, 1, 2}, 0), 4);
    check("missing", searchRotated({4, 5, 6, 7, 0, 1, 2}, 3), -1);
    check("not rotated", searchRotated({1, 2, 3, 4}, 4), 3);
    check("two elements", searchRotated({3, 1}, 1), 1);
    check("single", searchRotated({4}, 4), 0);
}
