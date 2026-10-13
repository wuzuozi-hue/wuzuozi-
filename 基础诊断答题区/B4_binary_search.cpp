// B4 练习：二分查找
// nums 已按升序排列。找到 target 就返回下标，找不到返回 -1。
// 例如 {2, 5, 8, 12, 17}，target = 12，返回 3。

#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& nums, int target) {
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) {
            return mid;
        }

        if (nums[mid] < target) {
            // TODO 1：中间的数太小，下一轮从哪里开始找？
            left = mid+1;
             // 占位：写出赋值语句后删掉这行
        } else {
            // TODO 2：中间的数太大，下一轮到哪里结束？
            right =  mid -1;
             // 占位：写出赋值语句后删掉这行
        }
    }

    return -1;
}

int main() {
    int passed = 0;
    if (binarySearch({2, 5, 8, 12, 17}, 12) == 3) ++passed;
    if (binarySearch({2, 5, 8, 12, 17}, 7) == -1) ++passed;
    if (binarySearch({}, 7) == -1) ++passed;

    std::cout << "通过 " << passed << "/3 个用例\n";
}
