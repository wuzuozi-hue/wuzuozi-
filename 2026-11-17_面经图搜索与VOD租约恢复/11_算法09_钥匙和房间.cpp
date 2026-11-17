#include <cassert>
#include <iostream>
#include <vector>

// 第 9 题：钥匙和房间（Medium）
// 一开始只能进入 0 号房间。rooms[i] 是 i 号房间里所有钥匙的编号。
// 拿到编号 j 的钥匙，就能进入 j 号房间。进入后可以取走里面的全部钥匙。
// 判断能否进入所有房间。至少有一个房间，钥匙编号都是有效下标。
//
// 示例：rooms = {{1}, {2}, {}, {0}}
// 0 --> 1 --> 2     3 --> 0
// 从 0 能到 1、2，但找不到 3 的钥匙，返回 false。

using Rooms = std::vector<std::vector<int>>;
void visit(const Rooms& rooms,std::vector<bool>& visited,int room){
    if(visited[room] == true){
        return ;
    }
    visited[room] = true;
    for(int key : rooms[room]){
        visit(rooms,visited,key);
    }
}

bool canVisitAllRooms(const Rooms& rooms) {
    std::vector<bool> visited(rooms.size(),false);
    visit(rooms,visited,0);
    for (bool seen : visited){
        if(!seen){
            return false;
        }
    }
    return true;
}

int main() {
    assert(canVisitAllRooms({{}}));
    assert(!canVisitAllRooms({{}, {0}}));
    assert(canVisitAllRooms({{1}, {2}, {3}, {}}));
    assert(!canVisitAllRooms({{1}, {2}, {}, {0}}));
    assert(canVisitAllRooms({{1, 2}, {0, 3}, {1}, {2}}));
    assert(!canVisitAllRooms({{1}, {0}, {3}, {2}}));
    assert(canVisitAllRooms({{1, 2}, {}, {3}, {}}));

    std::cout << "Keys and rooms: all checks passed\n";
}
