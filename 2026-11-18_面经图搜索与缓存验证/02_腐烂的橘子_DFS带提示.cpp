#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<int>>;

// 0 是空格，1 是新鲜橘子，2 是原本腐烂的橘子。
// 每分钟只往上下左右传播一格。返回所有新鲜橘子腐烂所需的分钟数，
// 有新鲜橘子始终无法到达则返回 -1。
//
//                 左侧更近    右侧更近
// 原图          [2] [1] [1] [1] [2]
// 最早腐烂时间   0   1   2   1   0
// 先用单起点手推 2 1 1，再看右端起点怎样把原来记下的 3 改成 1。

void rotDfs(const Grid& grid, Grid& time, int row, int col, int minute) {
    // 第 1 步：写越界、空格两种出口；坐标合法后才读取格子。
    // 第 2 步：比较本次 minute 与已记录的时间，判断何时需要继续。
    // 第 3 步：更新时间，先递归检查右边，再补左、上、下。
    int rows = grid.size();
    int cols = grid[0].size();
    if(row < 0 || row >=rows || col <0 || col >= cols){
        return ;
    }
    if(grid[row][col] == 0){
        return ;
    }
    int oldtime = time[row][col];
    if(oldtime != -1 && oldtime <= minute){
        return;
    }
    time[row][col] = minute;
    rotDfs(grid,time,row+1,col,minute +1);
    rotDfs(grid,time,row-1,col,minute +1);
    rotDfs(grid,time,row,col+1,minute +1);
    rotDfs(grid,time,row,col-1,minute +1);

}

int orangesRotting(const Grid& grid) {
    if (grid.empty() || grid[0].empty()) {
        return 0;
    }
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    Grid time(rows, std::vector<int>(cols, -1));
    for(int row = 0; row<rows;row++){
        for(int col =0; col <cols;col++){
            if(grid[row][col] == 2){
            rotDfs(grid,time,row,col,0);
            }
        }
    }
    int answer = 0;
     for(int row = 0; row<rows;row++){
        for(int col =0; col <cols;col++){
            if(grid[row][col] != 1){
                continue;
            }
            if(time[row][col] == -1){
                return -1;
            }
            answer = std::max(answer,time[row][col]);
        }
    }


    // 第 4 步：找到所有起点。从每个起点开始时，传入第几分钟？
    // 第 5 步：扫描原来新鲜的橘子。有格子仍为 -1 时返回什么？
    // 如果都能到达，要取这些时间中的最大值还是最小值？

    return answer;
}

int main() {
    assert(orangesRotting({{2, 1, 1}}) == 2);
    assert(orangesRotting({{2, 1, 1, 1, 2}}) == 2);
    assert(orangesRotting({{2, 0, 1}}) == -1);
    assert(orangesRotting({{1}}) == -1);
    assert(orangesRotting({{2, 1, 1}, {1, 1, 0}, {0, 1, 1}}) == 4);
    assert(orangesRotting({{0, 2}}) == 0);
    assert(orangesRotting({}) == 0);
    std::cout << "Rotting oranges DFS: all checks passed\n";
}
