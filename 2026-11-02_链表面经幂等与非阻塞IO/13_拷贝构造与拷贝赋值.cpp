#include <iostream>
#include <string>

class Job {
public:
    std::string id;

    explicit Job(std::string value) : id(value) {}

    // TODO 1：写拷贝构造函数，用 other.id 初始化 id，输出 "copy constructor"。
    Job(const Job& other) : id(other.id){
        std::cout<<"copy constructor\n";
    }

    Job& operator=(const Job&other){
        id = other.id;
        std::cout<<"copy assignment\n";
        return *this;
    }
    // TODO 2：写拷贝赋值运算符，将 other.id 赋给 id，输出 "copy assignment"，
    // 最后 return *this;。
};

int main() {
    Job a("J1");
    Job b = a;        // b 是新对象
    Job c("J3");
    c = a;            // c 已经存在
    std::cout << "a=" << a.id << " b=" << b.id << " c=" << c.id << '\n';

    // 预期：分别打印一次 copy constructor、copy assignment，
    // 最后输出 a=J1 b=J1 c=J1。
}
