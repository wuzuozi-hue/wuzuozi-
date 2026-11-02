#include <iostream>
#include <optional>
#include <string>

// 仅作教学分类模型：假设冲突后新任务事务已回滚，并成功查询到结果。
// 不包含真实事务、并发、键过期或模型配置等内容。
struct ExistingRequest {
    std::string jobId;
    std::string question;
};

enum class Decision { Reuse, Conflict, NotFound };

Decision decide(const std::optional<ExistingRequest>& existing,
                const std::string& incomingQuestion) {
    if(!existing.has_value()){
        return Decision::NotFound;
    }else{
        if(existing->question == incomingQuestion){
            return Decision::Reuse;
        }
        else{
            return Decision::Conflict;
        }
    }
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    ExistingRequest old{"J1", "what is RAII?"};
    check("same question", decide(old, "what is RAII?") == Decision::Reuse);
    check("different question", decide(old, "what is TCP?") == Decision::Conflict);
    check("no mapping", decide(std::nullopt, "what is RAII?") == Decision::NotFound);
}
