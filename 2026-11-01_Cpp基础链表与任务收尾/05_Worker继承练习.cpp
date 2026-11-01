#include <iostream>
#include <string>

struct Worker {
    std::string name;

    void introduce() const {
        std::cout << "worker: " << name << '\n';
    }
};

// TODO 1：写一个 MockWorker，让它 public 继承 Worker。
struct MockWorker : public Worker{
    void mockRun(){
        std::cout<<"mock task"<<std::endl;
    }
};
// TODO 2：在 MockWorker 中写 mockRun()，输出 "mock task"。

int main() {
    MockWorker worker;
    worker.name = "J1";
    worker.introduce();
    worker.mockRun();
    // 预期输出：
    // worker: J1
    // mock task
}
