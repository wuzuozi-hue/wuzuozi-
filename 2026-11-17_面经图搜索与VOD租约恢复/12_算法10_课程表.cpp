#include <cassert>
#include <iostream>
#include <vector>

// 第 10 题：课程表（Medium）
// 共有 numCourses 门课，编号 0～numCourses - 1。
// prerequisites 中每对 {a, b} 表示修 a 之前必须先修 b。
// 例如 {2, 1} 表示 1 → 2，箭头从先修课指向后修课。
// 判断能否修完全部课程。没有先修要求时可以修完。
//
// 能修完：0 → 1 → 2。
// 修不完：0 → 1 → 2 → 0，三门课都在等另一门课先修完。

using CourseList = std::vector<std::vector<int>>;
bool hascycle(const CourseList& adj,std::vector<int>& state,int cur){
    if(state[cur] == 1){
        return true;
    }
    if(state[cur] == 2){
        return false;
    }
    state[cur] = 1;
    for(int next :adj[cur]){
        if(hascycle(adj,state,next)){
            return true;
        }
    }
    state[cur] = 2;
    return false;
}
bool canFinish(int numCourses, const CourseList& prerequisites) {
    // 在这里实现，可以在上方添加 DFS 辅助函数。
    CourseList adj(numCourses);
    for(const auto& pair : prerequisites){
        int a =pair[0];
        int b = pair[1];
        adj[b].push_back(a);
    }
    std::vector<int> state(numCourses,0);
    for(int course = 0; course < numCourses; ++course){
        if(state[course] == 0){
            if(hascycle(adj,state,course)){
                return false;
            }
        }
    }
    return true;
}

int main() {
    assert(canFinish(1, {}));
    assert(canFinish(3, {{1, 0}, {2, 1}}));
    assert(!canFinish(2, {{1, 0}, {0, 1}}));
    assert(!canFinish(3, {{1, 0}, {2, 1}, {0, 2}}));
    assert(canFinish(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}}));
    assert(!canFinish(5, {{1, 0}, {3, 2}, {2, 3}}));
    assert(!canFinish(1, {{0, 0}}));

    std::cout << "Course schedule: all checks passed\n";
}
