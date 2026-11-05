#include <iostream>
#include <vector>

// 互不相同的升序数组经过旋转；返回目标下标，不存在返回 -1。
int searchRotated(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if(nums[left] < = nums[mid])
        
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
    check("two", searchRotated({3, 1}, 1), 1);
    check("single", searchRotated({4}, 4), 0);
}
