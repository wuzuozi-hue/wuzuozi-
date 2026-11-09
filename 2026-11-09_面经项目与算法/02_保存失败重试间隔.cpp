#include <iostream>
#include <limits>

// 项目小练习（不算在 10 道算法中）：有上限的保存重试间隔。
// failedAttempts 是已经发生的保存失败次数，不是“第几次发出请求”。
// 约定：0 次失败 -> 0 秒；1,2,3,4 次 -> 2,4,8,16 秒；5 次及以后 -> 30 秒。
// 即使 failedAttempts 很大，也必须快速返回，不能发生移位/乘法溢出。
// 本函数只计算秒数；不能 sleep，也不负责真正保存、定时或释放容量。
// 提示词：先处理边界；达到上限后不再翻倍。本人实现后解释理由。
int retryDelaySeconds(unsigned int failedAttempts) {
    if(failedAttempts == 0){
        return 0;
    }
    if(failedAttempts <=4 && failedAttempts >0){
        if(failedAttempts ==1)
        return 2;
        if(failedAttempts == 2)
        return 4;
        if(failedAttempts == 3)
        return 8;
        if(failedAttempts == 4)
        return 16;
    }
    return 30;
}

int main() {
    struct Case { unsigned int failures; int expected; };
    const Case cases[] = {
        {0, 0}, {1, 2}, {2, 4}, {3, 8}, {4, 16}, {5, 30}, {6, 30},
        {std::numeric_limits<unsigned int>::max(), 30}
    };
    int passed = 0;
    for (const auto& test : cases) {
        const int actual = retryDelaySeconds(test.failures);
        const bool ok = actual == test.expected;
        if (ok) ++passed;
        std::cout << "failures=" << test.failures << " expected=" << test.expected
                  << " actual=" << actual << ' ' << (ok ? "PASS" : "FAIL") << '\n';
    }
    std::cout << passed << "/8 passed\n";
    return passed == 8 ? 0 : 1;
}
