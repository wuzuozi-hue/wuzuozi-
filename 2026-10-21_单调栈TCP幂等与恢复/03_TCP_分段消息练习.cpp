// 2026-10-21：模拟 TCP 数据分段到达。此练习用已知长度划分消息。
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> takeFrame(std::string& buffer, std::size_t length) {
    // TODO：字节数不足时返回 std::nullopt，不修改 buffer。
    int n =buffer.size();
    if(n <length){
        return std::nullopt;
    }
    std::string frame = buffer.substr(0,length);
    buffer.erase(0,length);
    return frame;
    // 足够时只取出前 length 字节，剩余字节留给下一条消息。
}

int main() {
    std::string buffer = "HE";
    const auto first = takeFrame(buffer, 5);
    buffer += "LLOWO";
    const auto second = takeFrame(buffer, 5);
    buffer += "RLD";
    const auto third = takeFrame(buffer, 5);
    const bool ok = !first && second && *second == "HELLO" && third && *third == "WORLD" && buffer.empty();
    std::cout << (ok ? "PASS" : "FAIL") << '\n';
    return ok ? 0 : 1;
}
