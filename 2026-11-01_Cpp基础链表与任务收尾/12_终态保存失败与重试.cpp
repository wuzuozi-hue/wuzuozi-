#include <iostream>
#include <string>

// 教学模型：单线程、模拟数据库；不连接 DevDocQA 或真实数据库。
struct FakeDatabase {
    int failuresRemaining = 0;
    int calls = 0;
    std::string storedStatus;

    bool saveTerminal(const std::string& status) {
        ++calls;
        if (failuresRemaining > 0) {
            --failuresRemaining;
            return false;
        }
        storedStatus = status;
        return true;
    }
};

struct Task {
    std::string terminalStatus = "failed";
    bool saved = false;
    int slotsHeld = 1;
    int releaseCount = 0;
};

// 模拟一次保存尝试：返回 true 表示已保存，false 表示需要稍后重试。
bool attemptSave(Task& task, FakeDatabase& db) {
    if(task.saved == true){
        return true;
    }
    // TODO 1：task.saved 已经为 true 时，直接返回 true。
    if(db.saveTerminal(task.terminalStatus)  == false){
        return false;
    }else{
        task.saved = true;
        --task.slotsHeld;
        ++task.releaseCount;
        return true;
    }

    // TODO 2：调用 db.saveTerminal(task.terminalStatus)。
    //         如果保存失败，直接返回 false，保留名额。
    // TODO 3：保存成功后，把 task.saved 设为 true，
    //         归还 task 持有的一个名额，并把 releaseCount 加 1。
    //         然后返回 true。
   
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    Task job;
    FakeDatabase db;
    db.failuresRemaining = 1;

    bool first = attemptSave(job, db);
    check("first failure keeps slot", !first && !job.saved && job.slotsHeld == 1 && job.releaseCount == 0);

    bool second = attemptSave(job, db);
    check("retry saves and releases", second && job.saved && db.storedStatus == "failed" && job.slotsHeld == 0 && job.releaseCount == 1);

    bool third = attemptSave(job, db);
    check("no duplicate release", third && db.calls == 2 && job.slotsHeld == 0 && job.releaseCount == 1);

    Task another;
    FakeDatabase healthy;
    check("success on first try", attemptSave(another, healthy) && another.saved && another.slotsHeld == 0 && another.releaseCount == 1);
}
