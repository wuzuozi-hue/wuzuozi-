#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 独立的小练习：只判断请求应该怎么处理，不连接数据库。
// 真实并发场景仍需要数据库唯一约束，不能只靠这个函数防止重复创建。
enum class Decision {
    Create,    // 创建新任务
    Reuse,     // 返回已有任务
    Conflict   // 请求内容冲突
};

Decision decide(bool keyExists,
                const std::string& savedContent,
                const std::string& incomingContent) {
    // keyExists：是否已经存在这个幂等键。
    // savedContent：这个键第一次提交的内容。
    // incomingContent：本次提交的内容。

    // TODO 1：键不存在，返回 Decision::Create。
    if(!keyExists){
        return Decision::Create;
    }
    if(savedContent == incomingContent){
        return Decision::Reuse;
    }
    return Decision::Conflict;

}

// 以下测试区不用修改。字符串比较已经足够，不需要计算摘要。
const char* nameOf(Decision decision) {
    switch (decision) {
        case Decision::Create: return "Create";
        case Decision::Reuse: return "Reuse";
        case Decision::Conflict: return "Conflict";
    }
    return "Unknown";
}

int main() {
    struct Case {
        bool keyExists;
        std::string savedContent;
        std::string incomingContent;
        Decision expected;
    };
    const std::vector<Case> cases{
        {false, "", "RAII", Decision::Create},
        {true, "RAII", "RAII", Decision::Reuse},
        {true, "RAII", "TCP", Decision::Conflict},
        {false, "TCP", "TCP", Decision::Create},
        {true, "TCP", "tcp", Decision::Conflict}
    };
    int passed = 0;
    for (std::size_t i = 0; i < cases.size(); ++i) {
        const auto& c = cases[i];
        try {
            const Decision actual = decide(c.keyExists, c.savedContent, c.incomingContent);
            const bool ok = actual == c.expected;
            if (ok) ++passed;
            std::cout << "case " << i + 1 << ": " << (ok ? "PASS" : "FAIL")
                      << " actual=" << nameOf(actual)
                      << " expected=" << nameOf(c.expected) << '\n';
        } catch (const std::exception& e) {
            std::cout << "case " << i + 1 << ": " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
