#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

// 可在当前Windows工具链编译的C++练习：管理C标准库的FILE*。
// FILE*是文件流指针，与Linux的int文件描述符不是同一种类型；
// 这个练习用于验证共同的资源所有权和RAII思路，不冒充Linux close实测。
class FileGuard {
    std::FILE* file_;
    int& closedCount_; // 测试用：成功关闭一次时加1；计数器的生命周期由调用者保证。

public:
    // TODO 1：写构造函数FileGuard(std::FILE* file, int& closedCount)，
    // 用成员初始化列表初始化file_和closedCount_。
    FileGuard(std::FILE* file, int& closedCount)
        :file_(file),closedCount_(closedCount){
    }
    // TODO 2：禁止复制构造和复制赋值，避免两个对象都以为自己拥有同一个FILE*。
    FileGuard(const FileGuard&) =delete; //禁止赋值构造
    FileGuard& operator=(const FileGuard&) =delete;
    // TODO 3：写析构函数：file_非空时调用std::fclose(file_)；
    ~FileGuard(){
        if(file_ != nullptr){
            if(std::fclose(file_) == 0){
                ++closedCount_;
            }
        }
    }
    // 如果fclose返回0，说明关闭成功，将closedCount_加1。
};

// 以下是测试区，不需要修改。
static_assert(!std::is_copy_constructible<FileGuard>::value, "FileGuard must not be copy-constructed");
static_assert(!std::is_copy_assignable<FileGuard>::value, "FileGuard must not be copy-assigned");

int exerciseReturn(int& closedCount, bool early) {
    std::FILE* raw = std::tmpfile();
    if (!raw) return -1;
    FileGuard guard(raw, closedCount);
    if (early) return 7;
    return 0;
}

void exerciseException(int& closedCount) {
    std::FILE* raw = std::tmpfile();
    if (!raw) throw std::runtime_error("tmpfile failed");
    FileGuard guard(raw, closedCount);
    throw std::runtime_error("expected exception");
}

int main() {
    int normalClosed = 0;
    int earlyClosed = 0;
    int exceptionClosed = 0;
    const int normalResult = exerciseReturn(normalClosed, false);
    const int earlyResult = exerciseReturn(earlyClosed, true);
    bool caughtExpected = false;
    try {
        exerciseException(exceptionClosed);
    } catch (const std::runtime_error& e) {
        caughtExpected = std::string(e.what()) == "expected exception";
    }

    const bool normalOk = normalResult == 0 && normalClosed == 1;
    const bool earlyOk = earlyResult == 7 && earlyClosed == 1;
    const bool exceptionOk = caughtExpected && exceptionClosed == 1;
    std::cout << "normal return: " << (normalOk ? "PASS" : "FAIL") << '\n';
    std::cout << "early return: " << (earlyOk ? "PASS" : "FAIL") << '\n';
    std::cout << "exception: " << (exceptionOk ? "PASS" : "FAIL") << '\n';
    return normalOk && earlyOk && exceptionOk ? 0 : 1;
}
