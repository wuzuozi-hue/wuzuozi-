#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// 教学模型：将客户端指定的文档 ID 排序、去重；不解析请求，不计算哈希。
std::vector<std::string> normalizeIds(std::vector<std::string> ids) {
    std::sort(ids.begin(),ids.end());
    ids.erase(std::unique(ids.begin(),ids.end()),ids.end());
    return ids;
}

void check(const char* name, const std::vector<std::string>& actual,
           const std::vector<std::string>& expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", normalizeIds({}), {});
    check("sort", normalizeIds({"B", "A"}), {"A", "B"});
    check("deduplicate", normalizeIds({"B", "A", "A"}), {"A", "B"});
    check("same ids", normalizeIds({"A", "A"}), {"A"});
}
