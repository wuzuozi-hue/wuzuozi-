#include <iostream>
#include <optional>
#include <string>

// 教学模型：当 UPDATE 影响 0 行时，假设已经根据 ID 查询过数据库。
enum class UpdateResult { Updated, StateMatches, Conflict, Missing };

UpdateResult classify(int affectedRows,
                      const std::optional<std::string>& storedStatus,
                      const std::string& desiredStatus) {
    // 1. affectedRows == 1：返回 Updated。
    if(affectedRows == 1){
        return UpdateResult::Updated;
    }
    if(affectedRows == 0 && !storedStatus.has_value()){
        return UpdateResult::Missing;
    }
    if(affectedRows == 0 && storedStatus == desiredStatus){
        return UpdateResult::StateMatches;
    }
    return UpdateResult::Conflict;
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("updated", classify(1, std::nullopt, "failed") == UpdateResult::Updated);
    check("missing", classify(0, std::nullopt, "failed") == UpdateResult::Missing);
    check("state matches", classify(0, std::string("failed"), "failed") == UpdateResult::StateMatches);
    check("conflict", classify(0, std::string("succeeded"), "failed") == UpdateResult::Conflict);
    check("running is conflict", classify(0, std::string("running"), "failed") == UpdateResult::Conflict);
}
