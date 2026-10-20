// 2026-10-20：用单线程 C++ 模拟“只有 running 才能完成任务”。
// 这是理解 SQL 条件更新的练习，不具备数据库的并发原子性。
#include <iostream>
#include <string>

struct Job {
    std::string status = "running";
    int collection_version = 5;
};

bool finishSuccess(Job& job) {
    if(job.status!="running")
    return false;
    job.status = "succeeded";
    job.collection_version++;
    return true;


    // TODO 1：若 status 不是 "running"，立即返回 false。
    // TODO 2：否则改为 "succeeded"，版本号加 1，返回 true。
}

int main() {
    Job job;
    const bool first = finishSuccess(job);
    const bool second = finishSuccess(job);
    std::cout << first << ' ' << second << ' '
              << job.status << ' ' << job.collection_version << '\n';
    // 预期：1 0 succeeded 6
}
