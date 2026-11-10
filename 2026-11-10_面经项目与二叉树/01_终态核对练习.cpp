#include <cassert>
#include <iostream>
#include <optional>
#include <string>

// 独立练习：不连接数据库，不代表真实服务已经修改。
enum class Action { Release, Inspect, Retry, Conflict };

Action decide(bool sqlError, bool updated, bool lookupError,
              const std::optional<std::string>& storedStatus,
              const std::optional<std::string>& storedError,
              const std::string& expectedStatus, const std::string& expectedError) {
    if (sqlError) return Action::Retry;
    if (updated) return Action::Release;
    if (lookupError) return Action::Retry;
    if (!storedStatus || !storedError) return Action::Inspect;
    if (*storedStatus == expectedStatus && *storedError == expectedError)
        return Action::Release;
    return Action::Conflict;
}

int main() {
    using A = Action;
    assert(decide(false, true, false, {}, {}, "failed", "timeout") == A::Release);
    assert(decide(true, false, false, {}, {}, "failed", "timeout") == A::Retry);
    assert(decide(false, false, true, {}, {}, "failed", "timeout") == A::Retry);
    assert(decide(false, false, false, "failed", "timeout", "failed", "timeout") == A::Release);
    assert(decide(false, false, false, "failed", "other", "failed", "timeout") == A::Conflict);
    assert(decide(false, false, false, "succeeded", "", "failed", "timeout") == A::Conflict);
    assert(decide(false, false, false, {}, {}, "failed", "timeout") == A::Inspect);
    std::cout << "7 scenarios passed\n";
}
