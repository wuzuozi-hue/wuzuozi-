#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

// 第 8 题：腐烂的橘子（Medium）
// 网格里的 0 代表空格，1 代表新鲜橘子，2 代表腐烂橘子。
// 每过一分钟，当前所有腐烂橘子同时让上下左右相邻的新鲜橘子腐烂。
// 本分钟刚腐烂的橘子从下一分钟开始传播。斜对角不传播。
// 返回腐烂所有新鲜橘子所需的最少分钟数。做不到就返回 -1。
// 一开始没有新鲜橘子（含空网格），返回 0。
//
// 第 0 分钟   第 1 分钟   第 2 分钟
// 2 1 1 1 2   2 2 1 2 2   2 2 2 2 2
// 两端同时传播，答案是 2。

int orangesRotting(std::vector<std::vector<int>> grid) {
    if(grid.empty() || grid[0].empty()){
        return 0;
    }
    std::queue<std::pair<int,int>> q;
    int fresh = 0;
    int rows = grid.size();
    int cols= grid[0].size();
    for(int row =0;row < rows; row++){
        for(int col =0;col<cols;col++){
            if(grid[row][col] == 1){
                ++fresh;
            }
            if(grid[row][col] == 2){
                q.emplace(row,col);
            }
        }
    }
    int minutes = 0;
    const int dr[] = {0, 0, -1, 1};
    const int dc[] = {1, -1, 0, 0}; // 右、左、上、下
    while(!q.empty() && fresh > 0){
        int count = q.size();
        for(int i =0;i<count; i++){
            auto cell = q.front();
            q.pop();
            int row = cell.first;
            int col = cell.second;

            if(nc <cols && grid[row][nc] == 1){
                grid[row][nc] = 2;
                fresh--;
                q.emplace(row,nc);
            }
        }
    }
    return 0;
}

int main() {
    assert(orangesRotting({}) == 0);
    assert(orangesRotting({{0, 2}}) == 0);
    assert(orangesRotting({{1}}) == -1);
    assert(orangesRotting({{2, 0, 1}}) == -1);
    assert(orangesRotting({{2, 1, 1, 1, 2}}) == 2);
    assert(orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}) == 4);
    assert(orangesRotting({{2, 1, 1}, {0, 1, 1}, {1, 0, 1}}) == -1);

    std::cout << "Rotting oranges: all checks passed\n";
}
