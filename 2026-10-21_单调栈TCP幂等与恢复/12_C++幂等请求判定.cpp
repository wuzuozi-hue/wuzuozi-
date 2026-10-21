#include <iostream>
#include <optional>
#include <string>

// 独立逻辑练习：根据数据库已查到的记录决定如何回应。
// 此函数本身不解决并发；真正防重仍需数据库唯一约束和事务。
struct ExistingRequest {
    std::string request_hash;
    std::string job_id;
};

struct Decision {
    std::string action; // "create"、"reuse" 或 "conflict"
    std::string job_id; // 只有 reuse 时填旧任务 ID
};

Decision decideRequest(const std::optional<ExistingRequest>& existing,
                       const std::string& incoming_hash) {
    if (!existing.has_value()) {
        return {"create", ""};
    }

    if (existing->request_hash == incoming_hash) {
        return {"reuse", existing->job_id};
    }

    return {"conflict", ""};
}

int main() {
    const ExistingRequest old{"hash-A", "J1"};
    const Decision a = decideRequest(std::nullopt, "hash-A");
    const Decision b = decideRequest(old, "hash-A");
    const Decision c = decideRequest(old, "hash-B");

    const bool pass_a = a.action == "create" && a.job_id.empty();
    const bool pass_b = b.action == "reuse" && b.job_id == "J1";
    const bool pass_c = c.action == "conflict" && c.job_id.empty();
    std::cout << "new: " << (pass_a ? "PASS" : "FAIL") << '\n';
    std::cout << "same request: " << (pass_b ? "PASS" : "FAIL") << '\n';
    std::cout << "changed request: " << (pass_c ? "PASS" : "FAIL") << '\n';
    return (pass_a && pass_b && pass_c) ? 0 : 1;
}
