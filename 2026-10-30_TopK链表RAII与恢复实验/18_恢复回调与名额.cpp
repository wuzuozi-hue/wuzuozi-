#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

// 独立模型：这些行代表数据库返回的queued候选；不直接修改真实项目。
struct Job {
    std::string id;
    int ageSeconds;
};
struct RecoveryBatch {
    std::vector<std::string> ready;   // 可入队的任务
    std::vector<std::string> expired; // 进入超时处理的任务
    int released = 0;                 // 本次应归还的预留名额数
};

// 假设reservedSlots已在查询前预留，且0 <= rows.size() <= reservedSlots。
// loaded/pending代表查询结果返回时的最新内存状态；timeoutSeconds>0。
// 需要归还两类名额：
// 1. 预留数大于查询返回行数，差额归还。
// 2. 某一行的ID现在已加载或正在提交，跳过并归还该行名额。
// 其他行：年龄>=timeoutSeconds放expired，否则放ready；保留名额供后续处理。
RecoveryBatch processRows(const std::vector<Job>& rows,
                          const std::unordered_set<std::string>& loaded,
                          const std::unordered_set<std::string>& pending,
                          int reservedSlots,
                          int timeoutSeconds) {
    RecoveryBatch result;
    result.released =reservedSlots - rows.size();
    // TODO：计算查询少返回的名额，逐行去重、分类，并返回result。
   for(const Job& job : rows){
    if(loaded.count(job.id) > 0 || pending.count(job.id) > 0){
        ++result.released;
        continue;
    }
    if(job.ageSeconds >= timeoutSeconds){
        result.expired.push_back(job.id);
    }else{
        result.ready.push_back(job.id);
    }
   }
   return result;
    // 完成后删除下面五行占位代码。

}

// 以下测试区不用修改。
int main() {
    struct Case {
        std::vector<Job> rows;
        std::unordered_set<std::string> loaded;
        std::unordered_set<std::string> pending;
        int reservedSlots;
        int timeout;
        std::vector<std::string> ready;
        std::vector<std::string> expired;
        int released;
    };
    const std::vector<Case> cases{
        {{{"J2", 120}, {"J5", 25}}, {"J5"}, {}, 2, 120, {}, {"J2"}, 1},
        {{{"J2", 120}, {"J5", 25}}, {}, {}, 2, 120, {"J5"}, {"J2"}, 0},
        {{{"J2", 120}}, {}, {}, 2, 120, {}, {"J2"}, 1},
        {{}, {}, {}, 2, 120, {}, {}, 2},
        {{{"A", 5}}, {"A"}, {"A"}, 1, 120, {}, {}, 1},
        {{{"A", 15}, {"B", 119}, {"C", 121}}, {"A"}, {"B"}, 4, 120, {}, {"C"}, 3},
        {{{"B", 3}, {"A", 2}}, {}, {}, 2, 120, {"B", "A"}, {}, 0},
        {{{"X", 120}}, {}, {"X"}, 1, 120, {}, {}, 1}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const auto& c = cases[i];
        try {
            const auto actual = processRows(c.rows, c.loaded, c.pending, c.reservedSlots, c.timeout);
            const bool ok = actual.ready == c.ready && actual.expired == c.expired &&
                            actual.released == c.released;
            if (ok) ++passed;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
                      << " released=" << actual.released << " expected=" << c.released << '\n';
        } catch (const std::exception& e) {
            std::cout << "case " << i + 1 << ": " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
