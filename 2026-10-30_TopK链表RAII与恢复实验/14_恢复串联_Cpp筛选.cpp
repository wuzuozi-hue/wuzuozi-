#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

// SQL已选出queued候选。ageSeconds由测试表直接提供，用于固定可复现的数据。
struct Job {
    std::string id;
    int ageSeconds;
};
struct RecoveryResult {
    std::vector<std::string> ready;
    std::vector<std::string> expired;
};

// 第二步：结果返回后再次排除loaded/pending；过期候选放expired，其余放ready。
// 已排除的任务不进入任一结果；各结果保持输入顺序。timeoutSeconds>0。
RecoveryResult collectRecovery(const std::vector<Job>& candidates,
                               const std::unordered_set<std::string>& loaded,
                               const std::unordered_set<std::string>& pending,
                               int timeoutSeconds) {
    // TODO：本人编写核心筛选函数，完成后删除占位代码。
    RecoveryResult result;
    for(const Job& job : candidates){
        if(loaded.count(job.id) >0 ||pending.count(job.id) > 0){
            continue;
        }
        if(job.ageSeconds >= timeoutSeconds){
            result.expired.push_back(job.id);
        }else{
        result.ready.push_back(job.id);
        }
    }
    return result;
}

// 以下输入/输出适配代码由助手提供，不需要修改。
// 输入：timeout、候选数与(id age)；loaded数与ID；pending数与ID。
// 输出：一行READY后接ID，一行EXPIRED后接ID。
int main() {
    int timeoutSeconds = 0;
    int count = 0;
    if (!(std::cin >> timeoutSeconds >> count) || timeoutSeconds <= 0 || count < 0 || count > 1000) return 2;
    std::vector<Job> candidates;
    for (int i = 0; i < count; ++i) {
        Job job;
        if (!(std::cin >> job.id >> job.ageSeconds)) return 2;
        candidates.push_back(job);
    }
    std::unordered_set<std::string> loaded, pending;
    int loadedCount = 0, pendingCount = 0;
    if (!(std::cin >> loadedCount) || loadedCount < 0 || loadedCount > 1000) return 2;
    for (int i = 0; i < loadedCount; ++i) {
        std::string id;
        if (!(std::cin >> id)) return 2;
        loaded.insert(id);
    }
    if (!(std::cin >> pendingCount) || pendingCount < 0 || pendingCount > 1000) return 2;
    for (int i = 0; i < pendingCount; ++i) {
        std::string id;
        if (!(std::cin >> id)) return 2;
        pending.insert(id);
    }
    try {
        const RecoveryResult result = collectRecovery(candidates, loaded, pending, timeoutSeconds);
        std::cout << "READY";
        for (const auto& id : result.ready) std::cout << ' ' << id;
        std::cout << "\nEXPIRED";
        for (const auto& id : result.expired) std::cout << ' ' << id;
        std::cout << '\n';
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
