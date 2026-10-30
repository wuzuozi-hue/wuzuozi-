#include <iostream>
#include <memory>

struct Worker {
    // 纯虚函数：作为统一接口，具体的run行为由派生类实现。
    virtual void run() = 0;
    virtual ~Worker() = default;
};

// 已给出的例子：MockWorker实现接口，可以创建对象。
struct MockWorker : Worker {
    void run() override {
        std::cout << "mock worker\n";
    }
};

struct RealWorker : Worker {
    void run() override {
        std::cout<<"real worker\n";
    }
    // TODO：实现void run() override，输出 real worker 并换行。
};

int main() {
    std::unique_ptr<Worker> first = std::make_unique<MockWorker>();
    std::unique_ptr<Worker> second = std::make_unique<RealWorker>();

    first->run();
    second->run();
}

// 实现RealWorker后，预期依次输出mock worker、real worker。
// Worker仍然是抽象类，但允许用Worker指针指向具体派生对象。
// RealWorker未实现纯虚函数前也是抽象类，make_unique会编译失败；这属于待完成状态。
