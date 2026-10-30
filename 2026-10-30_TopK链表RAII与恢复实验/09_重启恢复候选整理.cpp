#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

// 使用vector模拟数据库已经读出的任务记录；本文件不连接真实数据库。
// 输入记录按数据库提供的顺序排列，ID互不重复。
struct Job {
    std::string id;
    std::string status;
    int ageSeconds;
};

struct RecoveryResult {
    std::vector<std::string> ready;   // 可以作为入队候选的任务ID
    std::vector<std::string> expired; // 已超时、需要走超时处理的任务ID
};

// 参数约定：timeoutSeconds > 0，任务年龄 >= 0。
// 依次遍历jobs：
// 1. 非queued、已经loaded或正在pending：跳过。
// 2. queued且年龄>=timeoutSeconds：ID加入expired。
// 3. 其余queued任务：ID加入ready。
// 两个结果分别保持输入顺序。这个模型暂不模拟容量和并发。
RecoveryResult collectRecovery(const std::vector<Job>& jobs,
                               const std::unordered_set<std::string>& loaded,
                               const std::unordered_set<std::string>& pending,
                               int timeoutSeconds) {
    RecoveryResult result;
    // TODO：遍历jobs，把符合条件的任务ID放进result对应的vector。

    for(const Job& job: jobs){
        if(job.status!="queued"||loaded.count(job.id)>0 ||pending.count(job.id)>0 ){
            continue;
        }
        if(job.ageSeconds >= timeoutSeconds){
            result.expired.push_back(job.id);
        }else
            result.ready.push_back(job.id);
    }
    return result;
    // 提示：result.ready.push_back(job.id)，另一组同理。

    // 实现后删除下面五行占位代码，并返回result。

}

// 以下是测试区，不需要修改。
int main() {
    struct Case {
        std::vector<Job> jobs;
        std::unordered_set<std::string> loaded;
        std::unordered_set<std::string> pending;
        int timeout;
        std::vector<std::string> ready;
        std::vector<std::string> expired;
    };
    const std::vector<Job> persisted{
        {"J1", "queued", 10}, {"J2", "queued", 120},
        {"J3", "failed", 15}, {"J4", "queued", 20}
    };
    const std::vector<Case> cases{
        {{}, {}, {}, 120, {}, {}},
        {persisted, {"J1"}, {"J4"}, 120, {}, {"J2"}},
        {persisted, {}, {}, 120, {"J1", "J4"}, {"J2"}},
        {{{"A", "queued", 0}}, {}, {}, 120, {"A"}, {}},
        {{{"A", "queued", 120}, {"B", "queued", 121}}, {}, {}, 120, {}, {"A", "B"}},
        {{{"A", "running", 1}, {"B", "succeeded", 1}}, {}, {}, 120, {}, {}},
        {{{"A", "queued", 130}}, {"A"}, {}, 120, {}, {}},
        {{{"B", "queued", 1}, {"A", "queued", 2}}, {}, {}, 120, {"B", "A"}, {}}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const auto& c = cases[i];
        try {
            auto actual = collectRecovery(c.jobs, c.loaded, c.pending, c.timeout);
            const bool ok = actual.ready == c.ready && actual.expired == c.expired;
            if (ok) ++passed;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL") << '\n';
        } catch (const std::exception& e) {
            std::cout << "case " << i + 1 << ": " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
