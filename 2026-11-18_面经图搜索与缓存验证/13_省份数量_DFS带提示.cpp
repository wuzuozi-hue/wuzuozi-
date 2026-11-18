#include <cassert>
#include <iostream>
#include <vector>

// 547. 省份数量
// matrix[i][j] == 1 表示城市 i 和 j 直接相连。城市间道路双向。
// 直接或间接相连的城市属于同一省份，返回省份总数。
// 例如 {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}} 有两个省份：{0, 1} 和 {2}。

using Matrix = std::vector<std::vector<int>>;

void visitProvince(const Matrix& matrix, std::vector<bool>& visited, int city) {
    // TODO 1：把当前城市 city 标记为已访问。
    visited[city] = true;
    const int n = static_cast<int>(matrix.size());
    for (int next = 0; next < n; ++next) {
        // TODO 2：如果 city 和 next 有路，而且 next 还没走过，递归访问 next。
        if(matrix[city][next] == 1 && visited[next] == false){
            visitProvince(matrix,visited,next);
        }
        // 看 matrix[city][next] 这一格来判断有没有路。
    }
}

int findCircleNum(const Matrix& matrix) {
    const int n = static_cast<int>(matrix.size());
    std::vector<bool> visited(n, false);
    int provinces = 0;
    for(int i =0;i<n;i++){
        if(visited[i] == false){
            ++provinces;
            visitProvince(matrix,visited,i);
        }
    }
    // TODO 3：遍历城市编号。每遇到一个还没走过的城市，省份数加一，
    // 再从这个城市出发，标记同一省份的其余城市。
    return provinces;
}

int main() {
    assert(findCircleNum({{1}}) == 1);
    assert(findCircleNum({{1, 1}, {1, 1}}) == 1);
    assert(findCircleNum({{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}) == 2);
    assert(findCircleNum({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}) == 3);
    assert(findCircleNum({{1, 1, 0}, {1, 1, 1}, {0, 1, 1}}) == 1);
    assert(findCircleNum({{1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}}) == 2);
    std::cout << "Number of provinces: all checks passed\n";
}
