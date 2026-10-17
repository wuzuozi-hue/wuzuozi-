#include <iostream>
#include <thread>

// 先预测输出，再运行。
// value 是 main 的局部变量；[&] 让 worker 按引用访问它。
int main() {
    int value = 5;
    std::thread worker([&] {
        value += 3;
    });

    worker.join();
    std::cout << "value=" << value << '\n';
}
