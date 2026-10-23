// 2026-10-22：小顶堆入门。只保留最大的 3 个数字。
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

int main() {
    // 默认 priority_queue 是大顶堆；greater<int> 改成小顶堆。
    std::priority_queue<int, std::vector<int>, std::greater<int>> heap;
    const std::vector<int> values{9, 7, 5, 8};
    const std::size_t k = 3;

    for (int value : values) {
        // TODO 1：把 value 放入 heap。
        heap.push(value);

        // TODO 2：如果元素个数超过 k，移除堆顶（最小值）。
        if (heap.size() > k) {
            heap.pop();
        }

    }

    // 最后保留 7、8、9，堆顶应该是 7。
    const bool ok = heap.size() == k && heap.top() == 7;
    std::cout << (ok ? "PASS" : "FAIL") << '\n';
    return ok ? 0 : 1;
}
