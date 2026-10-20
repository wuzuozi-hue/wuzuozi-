// 2026-10-20 C++ 新知识：weak_ptr 与回调生命周期
// 先预测两次 callback() 的输出，再运行验证。
#include <functional>
#include <iostream>
#include <memory>

struct TaskState {
    int job_id = 42;
    ~TaskState() { std::cout << "TaskState destroyed\n"; }
};

int main() {
    std::function<void()> callback;
    {
        auto owner = std::make_shared<TaskState>();
        std::weak_ptr<TaskState> weak = owner;
        callback = [weak] {
            // TODO 1：用 weak.lock() 尝试取得临时 shared_ptr。
            auto alive = weak.lock();
            if(alive == nullptr){
                std::cout<<"expired"<<std::endl;
            }
            else{
                std::cout<<alive->job_id<<std::endl;
            }
            // TODO 2：对象还在时打印 job_id；已销毁时打印 expired。

        };
        std::cout << "first: ";
        callback();
    }
    std::cout << "second: ";
    callback();
}
