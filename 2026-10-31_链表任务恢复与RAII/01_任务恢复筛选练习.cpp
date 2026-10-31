#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct Job {
    std::string id;
    int ageSeconds;
};

struct Result {
    std::vector<std::string> expired;
    std::vector<std::string> ready;
    int released = 0;
};

Result selectJobs(const std::vector<Job>& rows,
                  const std::unordered_set<std::string>& loaded,
                  int timeoutSeconds) {
    Result result;

    for (const Job& job : rows) {
        // 1. 已经在 loaded 里：result.released 加 1，跳过当前任务。
        // 提示：loaded.count(job.id) > 0，continue;
      if (loaded.count(job.id) > 0) {
        ++result.released;
        continue;
}
        if(job.ageSeconds >= timeoutSeconds){
            result.expired.push_back(job.id);
        }else{
            result.ready.push_back(job.id);
        }
        // 2. ageSeconds >= timeoutSeconds：加入 result.expired。
        //    否则加入 result.ready。提示：push_back(job.id)
    }

    return result;
}

int main() {
    std::vector<Job> rows{{"J1", 10}, {"J2", 120}, {"J3", 20}};
    std::unordered_set<std::string> loaded{"J1"};
    Result result = selectJobs(rows, loaded, 60);

    std::cout << "released: " << result.released << " (expected 1)\n";
    std::cout << "expired:";
    for (const auto& id : result.expired) std::cout << ' ' << id;
    std::cout << " (expected J2)\nready:";
    for (const auto& id : result.ready) std::cout << ' ' << id;
    std::cout << " (expected J3)\n";
}
