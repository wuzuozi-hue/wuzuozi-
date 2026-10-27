#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

struct Guard {
    int& used;
    explicit Guard(int& value) : used(value) { ++used; }
    ~Guard() { --used; }
    Guard(const Guard&) = delete;
    Guard& operator=(const Guard&) = delete;
};
void earlyReturn(int& used) { Guard g(used); return; }
void throwing(int& used) { Guard g(used); throw std::runtime_error("demo"); }

int main() {
    std::unordered_map<int, int> m{{4, 2}, {7, 1}};
    assert(m.find(3) == m.end());
    std::cout << "find missing, size=" << m.size() << '\n';
    assert(m.size() == 2);
    const int value = m[3];
    assert(value == 0 && m.size() == 3);
    std::cout << "operator[], size=" << m.size() << ", value=" << value << '\n';

    std::vector<int> v;
    v.reserve(3);
    assert(v.empty() && v.capacity() >= 3);
    std::cout << "after reserve, size=" << v.size() << '\n';
    v.resize(v.capacity());
    const auto oldCapacity = v.capacity();
    v.push_back(9);
    assert(v.capacity() > oldCapacity && v.size() == oldCapacity + 1);
    std::cout << "growth occurred; exact multiplier is not assumed\n";

    auto p = std::make_shared<int>(7);
    auto q = p;
    std::weak_ptr<int> observer = p;
    assert(p.use_count() == 2);
    p.reset();
    assert(q.use_count() == 1 && *q == 7 && !observer.expired());
    q.reset();
    assert(observer.expired());
    std::cout << "shared ownership: 2 -> 1 -> expired\n";

    auto a = std::make_unique<int>(9);
    auto b = std::move(a); // move construction
    std::unique_ptr<int> c;
    c = std::move(b);     // move assignment
    assert(!a && !b && c && *c == 9);
    std::cout << "unique ownership moved, value=" << *c << '\n';

    std::function<int()> callback;
    std::weak_ptr<int> watch;
    {
        auto task = std::make_shared<int>(42);
        watch = task;
        callback = [task] { return *task; };
        task.reset();
        assert(!watch.expired());
    }
    assert(callback() == 42);
    callback = {};
    assert(watch.expired());
    std::cout << "callback owner released\n";

    int used = 0;
    { Guard g(used); assert(used == 1); }
    assert(used == 0);
    earlyReturn(used);
    assert(used == 0);
    try { throwing(used); } catch (const std::runtime_error&) {}
    assert(used == 0);
    std::cout << "RAII normal / return / exception: used=0\n";
}
