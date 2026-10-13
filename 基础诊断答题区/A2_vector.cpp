#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2};

    std::cout << "添加前：元素数=" << v.size()
              << "，容量=" << v.capacity() << '\n';

    v.push_back(3);

    std::cout << "添加后：元素数=" << v.size()
              << "，容量=" << v.capacity() << '\n';

    // 添加完成后，再获取迭代器。
    auto it = v.begin();
    std::cout << "第一个元素：" << *it << '\n';

    ++it;
    std::cout << "第二个元素：" << *it << '\n';
}
