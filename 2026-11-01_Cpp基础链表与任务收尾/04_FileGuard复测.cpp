#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <type_traits>

// 调用者确保计数器的生命周期长于 FileGuard。
// FileGuard 对传入的非空文件负责关闭。
class FileGuard {
    std::FILE* file_;
    int& closedCount_;

public:
    FileGuard(std::FILE* file,int& closedCount)
        :file_(file),closedCount_(closedCount){}
    // 1. 构造函数：用初始化列表初始化 file_ 和 closedCount_。
    // 2. 禁止复制构造和复制赋值
    FileGuard(const FileGuard&) = delete;
    FileGuard& operator=(const FileGuard&) = delete;    
    // 3. 析构：file_ 非空时关闭文件，关闭成功则计数器加 1。
    ~FileGuard(){
        if(file_!=nullptr){
            if(std::fclose(file_) == 0){
                closedCount_++;
            }
        }
    }
};

static_assert(!std::is_copy_constructible<FileGuard>::value, "must not copy construct");
static_assert(!std::is_copy_assignable<FileGuard>::value, "must not copy assign");

void useFile(int& count, bool early, bool fail) {
    std::FILE* file = std::tmpfile();
    if (!file) throw std::runtime_error("tmpfile failed");
    FileGuard guard(file, count);
    if (early) return;
    if (fail) throw std::runtime_error("test exception");
}

int main() {
    int count = 0;
    try {
        useFile(count, false, false);
        std::cout << "normal: " << (count == 1 ? "PASS" : "FAIL") << '\n';
        useFile(count, true, false);
        std::cout << "early return: " << (count == 2 ? "PASS" : "FAIL") << '\n';
        try { useFile(count, false, true); }
        catch (const std::runtime_error&) {}
        std::cout << "exception: " << (count == 3 ? "PASS" : "FAIL") << '\n';
    } catch (const std::exception& e) {
        std::cerr << "setup failed: " << e.what() << '\n';
        return 1;
    }
}
