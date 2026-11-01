#include <iostream>
#include <string>

class Job {
public:
    // TODO 1：定义两个 std::string 成员：id 和 status。
    std::string id;
    std::string status;
    // TODO 2：写成员函数 show()，输出 id 和 status。
    void show(){
        std::cout << id << " " << status << std::endl;
    }
};

int main() {
    // TODO 3：创建两个 Job 对象。
    // 第一个 id 为 J1、status 为 queued；
    // 第二个 id 为 J2、status 为 running。
    Job first;
    first.id ="J1";
    first.status ="queued";
    Job second;
    second.id ="J2";
    second.status = "running";
    // TODO 4：分别调用两个对象的 show()。
    first.show();
    second.show();
    // 预期输出：
    // J1 queued
    // J2 running
}
