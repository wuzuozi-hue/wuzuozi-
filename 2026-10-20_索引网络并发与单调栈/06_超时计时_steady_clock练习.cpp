// 2026-10-20 新知识：用单调时钟判断任务是否超时。
// 项目 server.cpp 用 steady_clock 记录任务 deadline；墙上时钟用于时间戳/分钟窗口。
// 不需要真的睡眠：main 用固定时间点验证边界，结果稳定。
#include <chrono>
#include <iostream>

using Clock = std::chrono::steady_clock;

bool expired(Clock::time_point now, Clock::time_point deadline) {
    // TODO：当 now 已到达或超过 deadline 时返回 true。
    if(now >= deadline){
        return true;
    }

    // 提示：比较两个 time_point，不要用 system_clock 重新读取当前时间。
    return false;
}

int main() {
    const Clock::time_point start{};
    const auto deadline = start + std::chrono::seconds(5);
    const bool before = expired(start + std::chrono::seconds(4), deadline);
    const bool exactly = expired(start + std::chrono::seconds(5), deadline);
    const bool after = expired(start + std::chrono::seconds(7), deadline);

    std::cout << before << ' ' << exactly << ' ' << after << '\n';
    // 目标输出：0 1 1
    return (!before && exactly && after) ? 0 : 1;
}
