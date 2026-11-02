#include <iostream>

// 单线程练习模型：不连接数据库或真实服务。
struct Submission {
    bool pending = true;       // 数据库写入尚未完成
    bool slotHeld = true;      // 已预留一个容量名额
    bool queued = false;       // 是否加入等待队列
};

// 仅处理数据库回调；假设每个 Submission 只调用一次。
int finishSubmission(Submission& task, bool dbSucceeded) {
    // 1. 无论成功还是失败，都清除 pending。
    task.pending = false;
    if(dbSucceeded == false){
        task.slotHeld = false;
        return 503;
    }else{
        task.queued = true;
        return 202;
    }
   
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    Submission failed;
    int failedStatus = finishSubmission(failed, false);
    check("failure returns 503", failedStatus == 503);
    check("failure cleans pending and slot", !failed.pending && !failed.slotHeld && !failed.queued);

    Submission succeeded;
    int successStatus = finishSubmission(succeeded, true);
    check("success returns 202", successStatus == 202);
    check("success queues and keeps slot", !succeeded.pending && succeeded.slotHeld && succeeded.queued);
}
