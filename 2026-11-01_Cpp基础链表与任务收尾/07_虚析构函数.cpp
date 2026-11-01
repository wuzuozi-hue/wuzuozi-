#include <iostream>
#include <memory>

struct Worker {
    virtual void run() = 0;
    virtual ~Worker(){
        std::cout<<"destroy Worker\n";
    }
    // TODO：定义虚析构函数，输出 "destroy Worker"。
};

struct MockWorker : Worker {
    void run() override { std::cout << "run mock\n"; }
    ~MockWorker() override { std::cout << "destroy MockWorker\n"; }
};

int main() {
    std::unique_ptr<Worker> worker = std::make_unique<MockWorker>();
    worker->run();
    // main 结束时 unique_ptr 通过 Worker 指针删除实际的 MockWorker。
    // 正确输出顺序：run mock、destroy MockWorker、destroy Worker。
}
