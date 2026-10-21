// 2026-10-21：用 std::optional 明确表示“找到”或“找不到”。
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

struct Job {
    std::string id;
    std::string status;
};

std::optional<Job> findJob(const std::unordered_map<std::string, Job>& jobs,
                           const std::string& id) {
    // TODO：只查找，不向 jobs 插入新键。
    auto it = jobs.find(id);
    if(it == jobs.end()){
        return std::nullopt;
    }
    return it->second;
}

int main() {
    const std::unordered_map<std::string, Job> jobs{
        {"J1", {"J1", "queued"}},
        {"J2", {"J2", "failed"}},
    };
    const auto found = findJob(jobs, "J2");
    const auto missing = findJob(jobs, "J9");
    const bool ok = found.has_value() && found->status == "failed" && !missing.has_value();
    std::cout << (ok ? "PASS" : "FAIL") << '\n';
    return ok ? 0 : 1;
}
