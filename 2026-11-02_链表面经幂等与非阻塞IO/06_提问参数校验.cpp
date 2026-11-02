#include <cstddef>
#include <iostream>
#include <string>

// 教学练习：仅模拟请求体大小、问题是否为空和问题字节数三项检查。
// 不解析 JSON，不模拟真实接口的空白文本、UTF-8 合法性或 NUL 检查。
int validateQuestion(std::size_t bodyBytes, const std::string& question) {
    // TODO 1：请求体超过 16384 字节，返回 413。
    if(bodyBytes > 16384){
        return 413;
    }
    if(question.size() == 0 || question.size() > 4000){
        return 400;
    }
    return 200;
    // TODO 2：question 为空或超过 4000 字节，返回 400。
    // TODO 3：通过这三项检查，返回 200（仅表示本练习的检查通过）。
   
}

void check(const char* name, int actual, int expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("body too large first", validateQuestion(16385, ""), 413);
    check("body exact limit", validateQuestion(16384, "ok"), 200);
    check("empty question", validateQuestion(100, ""), 400);
    check("question exact limit", validateQuestion(5000, std::string(4000, 'a')), 200);
    check("question too long", validateQuestion(5000, std::string(4001, 'a')), 400);
    check("normal", validateQuestion(100, "hello"), 200);
}
