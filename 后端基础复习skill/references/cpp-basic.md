# C++ 基础：从对象到 STL

目标：独立写出可编译的 C++17 小程序，解释对象何时创建/销毁，正确使用 `string`、`vector`、迭代器与简单模板。来源：C01—C12；图见 [配图索引](figures.md)。

## 1. 值、引用、指针与生命周期

- `int x = 3` 创建一个有自己生命周期的对象；`int& r = x` 是对已有对象的引用；`int* p = &x` 保存地址。指针可以为空，引用在合法初始化后应绑定对象。
- 返回局部对象的**值**通常是安全的；返回指向局部对象的指针或引用会悬空。不要把“返回值优化”理解成返回了局部变量的地址。
- 作用域正常结束时，局部对象按构造完成的相反顺序析构。类成员按**声明顺序**构造、按相反顺序析构；不是按初始化列表书写顺序。

```cpp
// life.cpp  编译：g++ -std=c++17 -Wall -Wextra life.cpp -o life
#include <iostream>
#include <string>
#include <utility>

struct Person {
    std::string name;
    explicit Person(std::string n) : name(std::move(n)) {
        std::cout << "create " << name << '\n';
    }
    ~Person() { std::cout << "destroy " << name << '\n'; }
};

int main() {
    Person first{"A"};
    Person second{"B"};
    std::cout << first.name << " and " << second.name << '\n';
}
```

预期顺序：创建 A、创建 B、打印名字、销毁 B、销毁 A。这里 `std::move(n)` 需要 `<utility>`；编译时应显式包含实际使用的标准库头文件。

## 2. 构造、析构与 RAII

构造函数负责建立对象不变量，析构函数负责释放其拥有的资源。使用成员初始化列表直接构造成员；引用成员、`const` 成员和没有默认构造函数的成员必须在初始化列表中初始化（C04）。RAII 管理的资源不限于内存，还可以是锁、文件描述符或连接。首选 `std::vector`、`std::string`、`std::unique_ptr` 等拥有资源的类型，而非每个分支手写 `new`/`delete`（C05、C25）。

```cpp
#include <memory>
#include <iostream>

struct Item {
    ~Item() { std::cout << "released\n"; }
};

int main() {
    auto item = std::make_unique<Item>();
    std::cout << "working\n";
} // item 离开作用域，所持有的 Item 被销毁
```

要解释的是**谁拥有资源、何时结束所有权**。`std::unique_ptr` 不能直接复制；后续在 [C++ 进阶](cpp-advanced.md) 学移动与共享所有权。

## 3. `vector`：`size`、`capacity` 与迭代器

`size()` 是当前元素个数，`capacity()` 是已分配空间最多可容纳的元素数；`reserve(n)` 只要求至少 n 的容量，`resize(n)` 改变元素个数（C09 第 1—2 页）。`push_back` 可能触发重新分配，但增长倍数由实现决定，不能假设永远乘 2。重新分配后指向旧存储的指针、引用和迭代器失效；`erase` 还会使删除位置及之后的迭代器失效（C09 第 4—8 页）。

```cpp
// vector_safe.cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> values{3, 1, 4};
    values.reserve(8);                // 容量至少为 8，size 仍为 3
    values.push_back(2);
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i] << ' ';
    }
    std::cout << "size=" << values.size()
              << " capacity=" << values.capacity() << '\n';
}
```

练习：在 `push_back` 前记录 `capacity`，再添加元素直到容量变化；**只打印旧容量和新容量，不解引用此前保存的迭代器**。随后解释为什么 `reserve(8)` 不会让 `values[7]` 成为有效元素。

复制容器会得到独立的元素序列；这和在 [C++ 进阶](cpp-advanced.md) 中用 `std::move` 转移资源不同：

```cpp
// vector_copy.cpp  g++ -std=c++17 -Wall -Wextra vector_copy.cpp -o vector_copy
#include <iostream>
#include <vector>

int main() {
    std::vector<int> original{10, 20};
    std::vector<int> copy = original;
    copy[0] = 99;
    std::cout << original[0] << ' ' << copy[0] << '\n'; // 10 99
}
```

这里改变 `copy` 不影响 `original`。如果容器元素是裸指针，复制的是指针值，不会自动复制指针指向的对象；所以要先明确谁拥有被指向的资源。

## 4. 常用容器如何选

| 容器 | 适合 | 关键限制 |
|---|---|---|
| `string` | 文本拼接、查询、传参 | 容量变化也可能使内部字符地址失效。 |
| `vector<T>` | 连续存储、按下标读取、尾部追加 | 中间插入/删除需要移动后续元素。 |
| `list<T>` | 已持有迭代器的位置频繁插删 | 不支持随机下标，缓存局部性通常不如 `vector`。 |
| `stack<T>` / `queue<T>` | 只需要后进先出 / 先进先出 | 是容器适配器，不提供任意下标访问。 |

模板让同一算法用于多种类型，基础阶段先能读懂 `std::vector<int>`、写一个简单函数模板；进阶阶段再学推导与实例化规则（C06、C12）。

```cpp
template <class T>
T larger(T a, T b) {
    return a < b ? b : a;
}
```

这里按值返回，避免初学时误把返回的引用保存得比实参还久；代价是可能复制值。后续学习引用与性能取舍时再比较其他签名。

面试自测：`reserve` 与 `resize` 的区别是什么？`push_back` 后原迭代器一定失效吗？为什么返回 `std::string` 值安全，而返回局部 `std::string&` 不安全？
