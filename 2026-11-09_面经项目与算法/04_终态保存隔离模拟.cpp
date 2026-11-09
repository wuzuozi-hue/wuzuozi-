#include <iostream>

// 隔离练习：只模拟终态保存结果，不连接数据库、不操作真实任务。
// 一开始有一个名额被占用。每次调用模拟一次保存结果到达：
// - 保存失败：attempts 加 1，retries 加 1，继续占用名额；
// - 保存成功：attempts 加 1，标记 completed，并释放一个名额；
// - 完成后又到达旧回调：忽略，不计数、不再次释放。
// 这个模型用来练习规则，不表示实际项目已修改或已通过故障集成测试。
struct SaveState {
    int attempts = 0; // 保存尝试数
    int retries = 0; // 安排的重试数
    int reserved = 1; // 当前任务占用的名额数
    bool completed = false; // 终态是否已保存
};

void applySaveResult(SaveState& state, bool success) {
    if(state.completed == true){
        return ;
    }
    if(success == false){
        ++state.attempts;
        ++state.retries;
    }
    if(success == true){
        ++state.attempts;
        state.completed = true;
        --state.reserved;
    }
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, bool ok) {
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };

    SaveState task;
    applySaveResult(task, false);
    check("first failure keeps slot", task.attempts == 1 && task.retries == 1 &&
        task.reserved == 1 && !task.completed);
    applySaveResult(task, false);
    check("second failure keeps slot", task.attempts == 2 && task.retries == 2 &&
        task.reserved == 1 && !task.completed);
    applySaveResult(task, true);
    check("success releases once", task.attempts == 3 && task.retries == 2 &&
        task.reserved == 0 && task.completed);
    applySaveResult(task, true);
    check("late callback ignored", task.attempts == 3 && task.retries == 2 &&
        task.reserved == 0 && task.completed);
    SaveState other;
    check("new task independent", other.attempts == 0 && other.retries == 0 &&
        other.reserved == 1 && !other.completed);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
