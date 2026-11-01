#include <iostream>
#include <string>

class Job {
public:
    std::string id;

    explicit Job(std::string jobId) : id(jobId) {
        std::cout << "create " << id << '\n';
    }

    // TODO 1：写析构函数，输出 "destroy " 和 id，然后换行。
    ~Job(){
        std::cout<<"destory"<<id<<'\n';
    }
};

void process(bool earlyReturn) {
    Job outer("J1");
    {
        Job inner("J2");
        // TODO 2：earlyReturn 为 true 时在此处提前 return。
        if(earlyReturn == true){
            return;
        }
    }
    std::cout << "after inner scope\n";
}

int main() {
    std::cout << "normal\n";
    process(false);
    std::cout << "early return\n";
    process(true);
}
