#include <iostream>
#include <memory>
#include <string>

// 2026-10-16：对应 DevDocQA 回调中的 [task] 按值捕获。
// 先预测输出，再运行；重点区分对象生命周期和容量名额。
struct Job {
    std::string id = "J42";
    ~Job() { std::cout << "destroy " << id << '\n'; }
};

auto makeCallback() {
    auto task = std::make_shared<Job>();
    std::cout << "before capture: " << task.use_count() << '\n';
    auto done = [task] { std::cout << "callback: " << task->id << '\n'; };
    std::cout << "after capture: " << task.use_count() << '\n';
    return done;
}

int main() {
    auto done = makeCallback();
    std::cout << "after function\n";
    done();
    std::cout << "end main\n";
}
