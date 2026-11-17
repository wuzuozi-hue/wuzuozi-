#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

// 第 7 题：岛屿的最大面积（Medium）
// 1 是陆地，0 是水。上下左右连通的陆地算一座岛，每格面积是 1。
// 返回最大岛屿的面积。没有陆地或网格为空时返回 0。
//
// 原网格        两座岛
// 1 1 0 0      A A . .
// 1 0 0 1      A . . B
// A 有 3 格，B 有 1 格，返回 3。

using AreaGrid = std::vector<std::vector<int>>;
int area(AreaGrid& grid,int row,int col){
    int rows = grid.size();
    int cols = grid[0].size();
    if(row <0 || row >= rows || col <0 || col >= cols){
        return 0;
    }
    if(grid[row][col] != 1){
        return 0 ;
    }
    grid[row][col] = 0;
    int toatl = 1;

    toatl += area(grid,row,col + 1);
    toatl += area(grid,row,col - 1);
    toatl += area(grid,row + 1,col);
    toatl += area(grid,row - 1,col);
    return toatl;
}
int maxAreaOfIsland(AreaGrid grid) {
    // 在这里实现。可添加辅助函数，也可以修改 grid 这份副本。
    if(grid.empty()|| grid[0].empty()){
        return 0;
    }
    int rows = grid.size();
    int cols = grid[0].size();
    int best = 0;
    for(int row = 0;row<rows; row++){
        for(int col = 0;col <cols; col++){
            if(grid[row][col] == 1){
                int current = area(grid, row, col);
                best = std::max(current,best);
            }
        }
    }
    return best;
}

int main() {
    assert(maxAreaOfIsland({}) == 0);
    assert(maxAreaOfIsland({{0, 0}, {0, 0}}) == 0);
    assert(maxAreaOfIsland({{1}}) == 1);
    assert(maxAreaOfIsland({{1, 0}, {0, 1}}) == 1);
    assert(maxAreaOfIsland({{1, 1, 0, 0}, {1, 0, 0, 1}}) == 3);
    assert(maxAreaOfIsland({{1, 0, 1}, {0, 1, 1}}) == 3);
    assert(maxAreaOfIsland({{1, 1, 1}, {1, 1, 1}}) == 6);

    std::cout << "Max area of island: all checks passed\n";
}
