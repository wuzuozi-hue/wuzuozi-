#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

// 第 6 题：寻找图中是否存在路径（Easy）
// n 个节点编号为 0 到 n-1，每条 edges[i] = {a, b} 都是双向道路。
// 判断从 source 出发能否走到 destination。起点等于终点时返回 true。
//
// 示例：0 --- 1 --- 2     3 --- 4
// edges = {{0, 1}, {1, 2}, {3, 4}}。
// 0 到 2 能走到；0 到 4 走不到。
bool reach(const std::vector<std::vector<int>>& adj,
    std::vector<bool>& visited,int cur,int destination){
        if(cur == destination){
            return true;
        }
        visited[cur] = true;
        for(int next : adj[cur]){
            if(visited[next]){
                continue;
            }
            if(reach(adj,visited,next,destination))
                return true;
        }
    return false;
    }
bool validPath(int n, const std::vector<std::vector<int>>& edges,
               int source, int destination) {
    // 在这里实现。可以使用 DFS 或 BFS。
    std::vector<std::vector<int>> adj(n);
    for(const auto& edge : edges){
        int a = edge[0];
        int b = edge[1];
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    std::vector<bool> visited(n, false);
    return reach(adj, visited, source, destination);
}

int main() {
    assert(validPath(5, {{0, 1}, {1, 2}, {3, 4}}, 0, 2));
    assert(!validPath(5, {{0, 1}, {1, 2}, {3, 4}}, 0, 4));
    assert(validPath(3, {{0, 1}, {1, 2}}, 2, 0));
    assert(validPath(1, {}, 0, 0));
    assert(!validPath(3, {}, 0, 2));
    assert(!validPath(4, {{0, 1}, {1, 2}, {2, 0}}, 0, 3));
    assert(validPath(4, {{0, 1}, {1, 2}, {2, 0}, {0, 3}}, 2, 3));

    std::cout << "Graph path: all checks passed\n";
}
