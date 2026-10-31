#include <iostream>
#include <string>

// 单线程教学模型：不连接数据库，也不模拟真实并发或名额释放。
struct Task {
    bool finishing = false;
    int finishCount = 0;
    std::string outcome;
};

void beginFinish(Task& task, const std::string& outcome) {
    // TODO 1：如果已经开始收尾，直接 return。
    // TODO 2：标记正在收尾，并记录 outcome。
    // TODO 3：finishCount 加 1，表示启动了一次收尾。
    if(task.finishing == true){
        return ;
    }
    else{
        task.finishing = true;
        task.outcome = outcome;
        task.finishCount++;
    }
    
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    Task a;
    beginFinish(a, "job_timeout");
    beginFinish(a, "succeeded"); // 成功结果迟到
    check("timeout first", a.finishCount == 1 && a.outcome == "job_timeout");

    Task b;
    beginFinish(b, "succeeded");
    beginFinish(b, "job_timeout"); // 超时回调迟到
    check("success first", b.finishCount == 1 && b.outcome == "succeeded");

    Task c;
    beginFinish(c, "worker_failed");
    check("single callback", c.finishing && c.finishCount == 1 && c.outcome == "worker_failed");
}
