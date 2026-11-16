#include <cassert>
#include <string>

// 视频转码项目：判断某次任务认领能否提交完成结果。
// 模拟数据库中一条已经找到的任务记录；真实项目由 SQL 条件更新并检查影响行数。
// 只有以下条件全部满足时，返回 true：
// 1. 提交的 claim_id 与记录中的 claim_id 相同；
// 2. 记录的 status 为 1（处理中）；
// 3. 当前时间 now 小于租约截止时间 lease_until；到期时已不能提交。
// 这里的时间只用整数模拟，单位是秒；不需要读取系统时间。
//
// 例：记录 A1，status=1，lease_until=100
// 提交 A1，now=90 → true
// 提交旧标识 B1，now=90 → false
// 提交 A1，now=100 → false

struct Job {
    std::string claim_id;
    int status;
    int lease_until;
};

bool canComplete(const Job& job, const std::string& submitted_claim_id, int now) {
    // 请在这里实现；完成后保存，我来编译测试。
    if(job.claim_id == submitted_claim_id &&job.status == 1 && now< job.lease_until){
        return true;
    }
    return false;
}

int main() {
    Job job{"A1", 1, 100};
    assert(canComplete(job, "A1", 90));
    assert(!canComplete(job, "B1", 90));
    assert(!canComplete(job, "A1", 100));
    assert(!canComplete(job, "A1", 101));
    job.status = 2;
    assert(!canComplete(job, "A1", 90));
}
