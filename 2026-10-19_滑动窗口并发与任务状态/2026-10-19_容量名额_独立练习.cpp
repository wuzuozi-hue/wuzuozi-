// 2026-10-19 C++ 后端练习：接纳名额，不修改 DevDocQA 项目源码。
// workers=1、waiting=2 时最多接纳 3 个尚未完成的任务。

#include <cstddef>
#include <iostream>
#include <stdexcept>

class Capacity {
public:
    Capacity(std::size_t workers, std::size_t waiting)
        : limit_(workers + waiting) {}

    bool reserve() {
        if(used_ == limit_){
        return false;}
        ++used_;
        return true;


    }

    void release() {
        if(used_ ==0){
            throw std::logic_error("underflow");
        }
        --used_;
    }

    std::size_t used() const { return used_; }
    std::size_t available() const { return limit_ - used_; }

private:
    std::size_t limit_;
    std::size_t used_{0};
};

int main() {
    Capacity slots(1, 2);
    const bool a = slots.reserve();
    const bool b = slots.reserve();
    const bool c = slots.reserve();
    const bool d = slots.reserve();
    slots.release();
    const bool e = slots.reserve();

    std::cout << std::boolalpha << a << ' ' << b << ' ' << c << ' '
              << d << ' ' << e << " used=" << slots.used()
              << " available=" << slots.available() << '\n';

    bool underflowRejected = false;
    Capacity empty(1, 0);
    try {
        empty.release();
    } catch (const std::logic_error&) {
        underflowRejected = true;
    }
    std::cout << "underflow_rejected=" << std::boolalpha << underflowRejected << '\n';

    return (a && b && c && !d && e && slots.used() == 3 &&
            slots.available() == 0 && underflowRejected) ? 0 : 1;
}
