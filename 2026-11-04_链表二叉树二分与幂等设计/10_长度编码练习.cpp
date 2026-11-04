#include <iostream>
#include <string>

// 把 value 按“字节长度:内容”追加到 out。
void frame(std::string& out, const std::string& value) {
    // TODO：依次追加 value 的字节长度、冒号、value 本身。
    // 提示：std::to_string(value.size()) 将数字转成字符串。
    out += std::to_string(value.size());
    out += ":";
    out.append(value);
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    std::string first;
    frame(first, "ab"); frame(first, "c");
    std::string second;
    frame(second, "a"); frame(second, "bc");
    std::string empty;
    frame(empty, "");
    check("first", first == "2:ab1:c");
    check("second", second == "1:a2:bc");
    check("distinct", first != second);
    check("empty", empty == "0:");
}
