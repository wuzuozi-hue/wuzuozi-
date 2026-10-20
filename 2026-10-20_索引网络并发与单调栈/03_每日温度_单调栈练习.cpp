// 2026-10-20 算法新题：每一天还要等几天才遇到更高温度。
// 提示按需领取；先自己想双层循环，再尝试用栈保存等待中的下标。
#include <iostream>
#include <vector>

std::vector<int> dailyTemperatures(const std::vector<int>& temperatures) {
    std::vector<int> answer(temperatures.size(), 0);
    std::vector<int> waiting; // 保存还没有找到更高温度的“下标”

    for (int today = 0; today < static_cast<int>(temperatures.size()); ++today) {
        while (!waiting.empty() && temperatures[today] > temperatures[waiting.back()]) {
            // TODO 1：取出 waiting 最后一个下标，记为 earlier。
            int earlier = waiting.back();
            waiting.pop_back();
            // TODO 2：计算 answer[earlier] = today - earlier。
            answer[earlier] = today -earlier;
        }
        // TODO 3：把 today 放入 waiting。
        waiting.push_back(today);
    }
    return answer;
}
//30 28 31
// 0  1  2
int main() {
    const std::vector<int> input{73, 74, 75, 71, 69, 72, 76, 73};
    const std::vector<int> expected{1, 1, 4, 2, 1, 1, 0, 0};
    const auto actual = dailyTemperatures(input);
    std::cout << (actual == expected ? "sample passed" : "sample failed") << '\n';
    // 完成样例后，再加递减、全部相同和空数组三个测试。
}
