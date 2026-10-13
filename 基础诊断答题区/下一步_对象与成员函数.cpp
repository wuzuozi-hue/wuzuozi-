#include <iostream>
#include <string>

struct Person {
    std::string name;

    void greet() {
        // 练习：在这里打印“你好，”和这个对象的 name，最后换行。
        // 提示：std::cout << "你好，" << name << '\n';
    }
};

int main() {
    Person person;
    person.name = "wuzuozi";
    person.greet();
}
