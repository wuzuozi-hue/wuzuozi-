# C++ 进阶：所有权、动态绑定与容器机制

先能独立完成 [C++ 基础](cpp-basic.md) 的对象与 `vector` 练习，再进入本页。来源：C13—C25，尤其 C14 多态、C16—C22 关联容器、C23 C++11、C24 异常、C25 智能指针。

## 1. 复制、移动与资源所有权

**看赋值号左侧**：`Buffer b = std::move(a);` 在创建 `b`，调用移动构造；`b = std::move(c);` 中 `b` 已存在，调用移动赋值。`std::move` 只是把表达式转成可供移动操作使用的右值类别，本身不搬数据。移动后的源对象仍须可析构、可重新赋值；不要假定其 `size()` 必为 0。对 `const` 对象使用 `std::move` 也未必能移动：常见移动构造接收非 `const T&&`，此时可能退回复制，或因不能复制而编译失败。

```cpp
// move_buffer.cpp  g++ -std=c++17 -Wall -Wextra move_buffer.cpp -o move_buffer
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

struct Buffer {
    std::vector<int> data;
    explicit Buffer(std::size_t n) : data(n) {}
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    Buffer(Buffer&&) = default;
    Buffer& operator=(Buffer&&) = default;
};

int main() {
    Buffer a{2};
    a.data[0] = 7;
    Buffer b = std::move(a); // 新对象：移动构造
    Buffer c{1};
    c = std::move(b);        // 已有对象：移动赋值
    std::cout << c.data[0] << '\n'; // 7
}
```

`std::vector` 已自己管理内存，所以 `Buffer` 无需手写析构。若直接拥有文件描述符或 `new` 出的数组，则必须清晰定义释放、复制限制、移动与自赋值后的状态。优先组合标准库资源类型，减少手写规则（C23、C25）。

## 2. 智能指针与异步生命周期

`unique_ptr<T>` 表示独占所有权；`shared_ptr<T>` 表示共享所有权；`weak_ptr<T>` 只观察由 `shared_ptr` 管理的对象，不增加共享计数，可用于避免环。`std::move(p)` 之后只有实际发生移动构造/赋值，所有权才转出。`p.get()` 给出被管理对象的裸指针，但不转移所有权，不能手动 `delete` 它。

异步回调里最要紧的是：**回调执行时捕获的对象还活着吗？** 不要仅为“让代码能编译”就把所有对象都换成 `shared_ptr`；先画出谁创建任务、谁持有回调、何时取消。若框架需要可复制回调，捕获 `unique_ptr` 的 lambda 可能不符合接口要求，这需要按框架签名选择所有权设计，而非盲目改成裸指针。

```cpp
// weak_callback.cpp  g++ -std=c++17 -Wall -Wextra weak_callback.cpp -o weak_callback
#include <functional>
#include <iostream>
#include <memory>

struct State { int value = 10; };

int main() {
    std::function<void()> on_done;
    {
        auto owner = std::make_shared<State>();
        on_done = [weak = std::weak_ptr<State>(owner)] {
            if (auto alive = weak.lock()) std::cout << alive->value << '\n';
            else std::cout << "expired\n";
        };
        on_done(); // owner 仍存活：输出 10
    }
    on_done();     // owner 已销毁：输出 expired
}
```

`weak.lock()` 成功时临时取得共享所有权，供本次回调安全使用；它不负责取消已提交的任务，也不替代任务状态检查。

## 3. 多态与析构

通过基类指针/引用调用被派生类覆盖的虚函数，才能得到运行时动态绑定。覆盖时写 `override`，让编译器检查签名；经基类指针销毁派生对象时，基类析构函数应为 `virtual`（C14）。

```cpp
// polymorphism.cpp
#include <iostream>
#include <memory>

struct Job {
    virtual ~Job() = default;
    virtual const char* run() const = 0;
};
struct IndexJob : Job {
    const char* run() const override { return "index"; }
};

int main() {
    std::unique_ptr<Job> job = std::make_unique<IndexJob>();
    std::cout << job->run() << '\n';
}
```

[虚函数调用图](../assets/figures/cpp-virtual-dispatch_C14_p11.png) 展示一种常见实现；C++ 标准要求的是可观察行为，并不规定必须存在图中的 `vptr/vtable` 布局。按值存入 `Job` 会遇到抽象类无法实例化；普通基类按值接收派生对象还可能发生对象切片。

## 4. 关联容器与哈希

| 容器 | 关键性质 | 典型用法 |
|---|---|---|
| `std::map` / `std::set` | 有序；查找、插入、删除通常是对数复杂度 | 需要按键排序或范围遍历。 |
| `std::unordered_map` / `std::unordered_set` | 无序；平均常数时间，极端冲突下可退化 | 两数之和、计数、按 ID 快速查询。 |

普通二叉搜索树若按已排序键持续插入，可能退化成高度为 `n` 的链；AVL 和红黑树通过维护平衡让树高保持对数量级（C15、C17—C19）。哈希表则用哈希值定位桶，需处理冲突与负载因子，扩容重哈希有一次性成本（C20—C22）。这些结构解释容器性能，但标准库没有要求 `std::map` 必须使用某一份课件里的红黑树节点布局。

`operator[]` 查不存在的键会插入默认值；只想检查存在性，用 `find` 或 `count`。重哈希可使 `unordered_map` 的迭代器失效；不要在遍历时假设桶布局不变。[红黑树变色示例](../assets/figures/cpp-red-black-recolor_C18_p6.png) 适合解释为何有序树需要维护平衡，初次面试先讲性质与复杂度。

```cpp
// first_repeat.cpp  返回同一个数前后两次出现的下标
#include <iostream>
#include <unordered_map>
#include <vector>

std::vector<int> first_repeat(const std::vector<int>& nums) {
    std::unordered_map<int, int> seen; // 数字 -> 首次出现的下标
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (auto it = seen.find(nums[i]); it != seen.end())
            return {it->second, i};
        seen.emplace(nums[i], i);
    }
    return {};
}

int main() {
    auto pair = first_repeat({8, 4, 6, 4});
    std::cout << pair[0] << ' ' << pair[1] << '\n'; // 1 3
}
```

练习：把 `find` 换成 `seen[nums[i]]` 会发生什么？先用 `{8, 4, 6, 4}` 手推，再观察映射中被意外插入的键。

## 5. 异常安全

异常可能让函数在中途退出。用 RAII 保证已成功取得的资源随对象析构释放；先建立临时新状态，成功后再提交，可减少“对象只更新了一半”的风险。区分基本保证（对象仍有效、无资源泄漏）与强保证（失败后效果等同操作未发生）。课件 C24 的异常示例需要结合实际编译和调用路径判断，不把 `catch (...)` 当作掩盖所有错误的常规手段。

面试自测：为什么 `std::move(a)` 单独写一行并不会让 `a` 变空？`map` 和 `unordered_map` 怎样选？通过 `Job*` 删除 `IndexJob` 为什么要虚析构？
