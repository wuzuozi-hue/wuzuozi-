#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 把文档 ID 排序并去重，返回处理后的列表。
// 例：{"B", "A", "A"} -> {"A", "B"}
// 空列表返回空列表；输入参数本身不需要修改。
std::vector<std::string> normalizeIds(std::vector<std::string> ids) {
    std::sort(ids.begin(),ids.end());
    ids.erase(std::unique(ids.begin(),ids.end()),ids.end());

    return ids;
}

int main() {
    int failed = 0;
    auto check = [&](const char* name, std::vector<std::string> input,
                     const std::vector<std::string>& expected) {
        const bool ok = normalizeIds(input) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) ++failed;
    };
    check("duplicates and order", {"B", "A", "A"}, {"A", "B"});
    check("empty", {}, {});
    check("same IDs", {"C", "C", "C"}, {"C"});
    check("already sorted", {"A", "B", "C"}, {"A", "B", "C"});
    check("non-adjacent duplicates", {"C", "A", "B", "C", "A"}, {"A", "B", "C"});
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
