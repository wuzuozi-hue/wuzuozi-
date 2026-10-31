#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <type_traits>

// 调用者保证 closedCount 的生命周期长于 FileGuard。
// 构造成功后，FileGuard 负责关闭传入的非空文件。
class FileGuard {
    std::FILE* file_;
    int& closedCount_;

public:
    // TODO 1：写构造函数 FileGuard(std::FILE* file, int& closedCount)
    // 用成员初始化列表初始化 file_ 和 closedCount_。
    FileGuard(std::FILE* file, int &closedCount)
    :file_(file),closedCount_(closedCount){}
    // TODO 2：禁止复制构造和复制赋值，避免两个对象关闭同一个文件。
    FileGuard(const FileGuard&) =delete;
    FileGuard& operator=(const FileGuard&) =delete;
    // TODO 3：写析构函数；file_ 非空时关闭一次；
    // std::fclose(file_) 返回 0 时，将 closedCount_ 加 1。
    ~FileGuard(){
        if(file_ != nullptr){
        if(std::fclose(file_) == 0){
            closedCount_++;
        }
    }
    }
};

static_assert(!std::is_copy_constructible<FileGuard>::value, "copy constructor must be deleted");
static_assert(!std::is_copy_assignable<FileGuard>::value, "copy assignment must be deleted");

void exercise(int& count, bool earlyReturn, bool raiseError) {
    std::FILE* file = std::tmpfile();
    if (!file) throw std::runtime_error("tmpfile failed");
    FileGuard guard(file, count);
    if (earlyReturn) return;
    if (raiseError) throw std::runtime_error("test exception");
}

int main() {
    int count = 0;
    try {
        exercise(count, false, false);
        std::cout << "normal: " << (count == 1 ? "PASS" : "FAIL") << '\n';
        exercise(count, true, false);
        std::cout << "early return: " << (count == 2 ? "PASS" : "FAIL") << '\n';
        try { exercise(count, false, true); }
        catch (const std::runtime_error&) { }
        std::cout << "exception: " << (count == 3 ? "PASS" : "FAIL") << '\n';
    } catch (const std::exception& e) {
        std::cerr << "test setup failed: " << e.what() << '\n';
        return 1;
    }
}
