// 2026-10-22：任务状态转移练习。先预测测试结果，再完成 TODO。
#include <iostream>

enum class JobStatus { queued, running, succeeded, failed };

bool canTransition(JobStatus from, JobStatus to) {
    // TODO：只允许 queued -> running；running -> succeeded 或 failed。
    // 其他转移都返回 false。先想清楚，再写 if 或 switch。
    if(from == JobStatus::queued && to == JobStatus::running){return true;}
    if(from == JobStatus::running&& to == JobStatus::succeeded){return true;}
    if(from == JobStatus::running && to == JobStatus::failed){return true;}

    return false;
}

int main() {
    struct Case { JobStatus from; JobStatus to; bool expected; };
    const Case cases[] = {
        {JobStatus::queued, JobStatus::running, true},
        {JobStatus::running, JobStatus::succeeded, true},
        {JobStatus::running, JobStatus::failed, true},
        {JobStatus::queued, JobStatus::succeeded, false},
        {JobStatus::succeeded, JobStatus::running, false},
        {JobStatus::failed, JobStatus::failed, false},
    };
    int passed = 0;
    for (const auto& test : cases) {
        if (canTransition(test.from, test.to) == test.expected) ++passed;
    }
    std::cout << passed << "/" << (sizeof(cases) / sizeof(cases[0])) << " passed\n";
    return passed == static_cast<int>(sizeof(cases) / sizeof(cases[0])) ? 0 : 1;
}
