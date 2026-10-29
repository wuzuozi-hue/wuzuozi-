    #include <iostream>

// Worker是基类，提供一个可以被派生类重新实现的run函数。
struct Worker {
    virtual void run() {
        std::cout << "normal worker\n";
    }
};

// : Worker表示MockWorker继承Worker；这里的struct继承默认是public。
struct MockWorker : Worker {
    // override要求编译器检查：这个函数确实覆盖了基类的虚函数。
    void run() override {
        std::cout << "mock worker\n";
    }
};
struct RealWorker : Worker {
    void run() override{
        std::cout<<"real worker\n";
    }
};

int main() {
    Worker first;
    MockWorker second;

    Worker* p = &first;
    p->run();                // 第一次调用：请先预测输出。

    p = &second;
    p->run();
    RealWorker third;
    p = &third;
    p->run();    // 第二次调用：请先预测输出。
}

// 本例对象都在栈上，p只观察它们，不负责delete。
// 后续再单独学习：通过基类指针销毁派生对象时，为什么需要虚析构。
