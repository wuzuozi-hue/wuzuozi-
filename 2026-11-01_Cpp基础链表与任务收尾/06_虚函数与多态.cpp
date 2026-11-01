#include <iostream>

struct Worker {
    // TODO 1：为 run 加上 virtual。
    virtual void run() {
        std::cout << "worker\n";
    }
};

struct MockWorker : public Worker {
    // TODO 2：在 run() 后加 override。
    void run() override{
        std::cout << "mock\n";
    }
};

struct RealWorker : public Worker {
    // TODO 3：写 run()，使用 override 并输出 "real"。
    void run() override{
        std::cout<<"real\n";
    }
};

int main() {
    MockWorker mock;
    RealWorker real;
    Worker* p = &mock;
    p->run();
    p = &real;
    p->run();
    // 预期输出：
    // mock
    // real
}
