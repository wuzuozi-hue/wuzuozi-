#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

// 独立练习：模拟一次查询后对候选任务的筛选，不修改真实服务。
struct Job {
    std::string id;
    std::string status;
    int ageSeconds;
};

enum class RecoveryChoice {
    Ignore,  // 非queued，或当前已加载/正在提交：跳过这次恢复
    Expired, // queued但已达到超时时限：需要走超时处理
    Ready    // 可以作为入队候选
};

// 参数约定：timeoutSeconds > 0，ageSeconds >= 0。
// 按以下顺序判断：
// 1. status不是queued，或id在loaded/pending集合中：Ignore。
// 2. 年龄达到或超过超时秒数：Expired。
// 3. 其他情况：Ready。
RecoveryChoice decideRecovery(const Job& job,
                              const std::unordered_set<std::string>& loaded,
                              const std::unordered_set<std::string>& pending,
                              int timeoutSeconds) {
    // 在这里写判断。完成后删除下面五行占位代码。
    if(job.status!="queued" || loaded.count(job.id) > 0|| pending.count(job.id) > 0){
        return RecoveryChoice::Ignore;
    }
    if(job.ageSeconds >= timeoutSeconds){
        return RecoveryChoice::Expired;
    }
    return RecoveryChoice::Ready;
}

// 以下测试区不需要修改。
const char* nameOf(RecoveryChoice choice) {
    switch (choice) {
        case RecoveryChoice::Ignore: return "Ignore";
        case RecoveryChoice::Expired: return "Expired";
        case RecoveryChoice::Ready: return "Ready";
    }
    return "Unknown";
}

int main() {
    struct Case {
        Job job;
        std::unordered_set<std::string> loaded;
        std::unordered_set<std::string> pending;
        int timeout;
        RecoveryChoice expected;
    };
    const std::vector<Case> cases{
        {{"J1", "queued", 12}, {}, {}, 120, RecoveryChoice::Ready},
        {{"J1", "queued", 12}, {"J1"}, {}, 120, RecoveryChoice::Ignore},
        {{"J1", "queued", 12}, {}, {"J1"}, 120, RecoveryChoice::Ignore},
        {{"J1", "running", 130}, {}, {}, 120, RecoveryChoice::Ignore},
        {{"J2", "queued", 120}, {}, {}, 120, RecoveryChoice::Expired},
        {{"J2", "queued", 121}, {}, {}, 120, RecoveryChoice::Expired},
        {{"J2", "queued", 119}, {}, {}, 120, RecoveryChoice::Ready},
        {{"J3", "failed", 20}, {}, {}, 120, RecoveryChoice::Ignore},
        {{"J1", "queued", 130}, {"J1"}, {}, 120, RecoveryChoice::Ignore}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const auto& c = cases[i];
        try {
            const auto actual = decideRecovery(c.job, c.loaded, c.pending, c.timeout);
            const bool ok = actual == c.expected;
            if (ok) ++passed;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
                      << " actual=" << nameOf(actual)
                      << " expected=" << nameOf(c.expected) << '\n';
        } catch (const std::exception& e) {
            std::cout << "case " << i + 1 << ": " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
