#include <iostream>
#include <string>

class Job {
public:
    std::string id;
    std::string status;
    Job(std::string jobId,std::string jobStatus)
        :id(jobId),status(jobStatus){};
    // TODO：写构造函数 Job(std::string jobId, std::string jobStatus)，
    // 使用初始化列表初始化 id 和 status。

    void show() const {
        std::cout << id << " " << status << '\n';
    }
};

int main() {
    Job first("J1", "queued");
    Job second("J2", "running");
    first.show();
    second.show();
}
