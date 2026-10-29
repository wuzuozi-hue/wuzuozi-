#include <iostream>
#include <memory>

struct Worker {
    // 基类析构函数是virtual，允许通过基类指针正确销毁派生对象。
    virtual ~Worker() {
        std::cout << "~Worker\n";
    }
};

struct RealWorker : Worker {
    // 基类析构函数是虚函数，因此派生类析构函数可以写override。
    ~RealWorker() override {
        std::cout << "~RealWorker\n";
    }
};

int main() {
    // 指针管理接口是Worker，实际创建的对象是RealWorker。
    std::unique_ptr<Worker> p = std::make_unique<RealWorker>();

    std::cout << "before reset\n";
    p.reset();
    std::cout << "after reset\n";
}

// 先预测reset期间两个析构函数的顺序，再运行。
// 请保留virtual；删掉virtual后的基类删除不是安全的对照实验。
// 不要将无虚析构时的行为简单描述为“一定只调用基类析构”。
