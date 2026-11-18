#include <cassert>
#include <iostream>
#include <vector>

// 1971. 寻找图中是否存在路径
// n 个节点从 0 到 n - 1 编号。每条 {a, b} 都是双向边。
// 判断能否从 source 到达 destination。起点等于终点时返回 true。
// 例：{{0, 1}, {1, 2}, {3, 4}} 中，0 能到 2，但到不了 4。
// 邻接表记录每个节点能直接走到哪里。
// 例如边 {0, 1} 要存两份：节点 0 的名单里加 1，节点 1 的名单里加 0。

using Graph = std::vector<std::vector<int>>;

bool reach(const Graph& adj, std::vector<bool>& visited,
           int current, int destination) {
    // TODO 2：已经走到终点，返回 true。否则把当前节点记为走过。
    if(current == destination){
        return true;
    }else{
        visited[current] = true;
    }
    // TODO 3：遍历 adj[current]，跳过走过的邻居。
    // 对没走过的邻居调用 reach，其中一条路走通就返回 true。
    for(int next : adj[current]){
        if(visited[next]){
            continue;
        }
        if(reach(adj,visited,next,destination)){
            return true;
        }
    }

    return false;
}

bool validPath(int n, const std::vector<std::vector<int>>& edges,
               int source, int destination) {
    Graph adj(n);
    for (const auto& edge : edges) {
        int a = edge[0];
        int b = edge[1];
        // TODO 1：用两次 push_back，把这条双向边存进 adj。
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
