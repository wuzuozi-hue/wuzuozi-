// 两数之和：哈希表版的第一步
// seen[数字] = 这个数字之前出现的下标。
// 例子：之前在下标0见过数字3，就写 seen[3] = 0。
// 当前又遇到数字3，目标是6；需要找“目标 - 当前数字”。

#include <iostream>
#include <unordered_map>

int main() {
    std::unordered_map<int, int> seen;
    seen[3] = 0;

    int target = 6;
    int current = 3;
    int need = 0;  // 请改成：目标减去当前数字

    if (seen.count(need) > 0) {
        std::cout << "之前出现的位置：" << seen[need] << '\n';
    } else {
        std::cout << "之前没见过需要的数字\n";
    }
}
