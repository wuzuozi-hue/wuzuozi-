#include <iostream>
#include <memory>
#include <stdexcept>

// 任务：对象还活着时返回对象中的整数，否则返回 fallback。
// 例如：对象值为10且仍存活，返回10；对象已销毁且fallback为-1，返回-1。
int readOr(const std::weak_ptr<int>& w, int fallback) {
    // TODO 1：调用 w.lock()，用 auto alive 接收返回的 shared_ptr。
    auto alive = w.lock();
    // TODO 2：如果 alive 非空，返回它所指向的整数。
    if(alive){
        return *alive;
    }
    return fallback;

}

// 以下是测试区，不需要修改。
int main() {
    int passed = 0;
    int total = 0;
    const auto check = [&](const char* label, const std::weak_ptr<int>& w,
                           int fallback, int expected) {
        ++total;
        try {
            const int actual = readOr(w, fallback);
            const bool ok = actual == expected;
            if (ok) ++passed;
            std::cout << label << ": " << (ok ? "PASS" : "FAIL")
                      << " actual=" << actual << " expected=" << expected << '\n';
        } catch (const std::exception& e) {
            std::cout << label << ": " << e.what() << '\n';
        }
    };

    auto owner = std::make_shared<int>(10);
    std::weak_ptr<int> observer = owner;
    check("live value 10", observer, -1, 10);
    *owner = 0;
    check("live value 0", observer, -1, 0);

    auto keeper = observer.lock();
    owner.reset();
    check("keeper still owns", observer, -1, 0);

    keeper.reset();
    check("last owner released", observer, -1, -1);

    std::weak_ptr<int> empty;
    check("empty observer", empty, 99, 99);

    std::cout << passed << '/' << total << " passed\n";
    return passed == total ? 0 : 1;
}
