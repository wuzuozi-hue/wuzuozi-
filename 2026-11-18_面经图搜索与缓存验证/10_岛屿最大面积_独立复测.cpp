#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

// 695. 岛屿的最大面积
// 1 是陆地，0 是水。上下左右连起来的陆地属于同一座岛。
// 面积是该岛的陆地格子数，返回最大的岛屿面积。没有陆地时返回 0。
// 例如 {{1, 1, 0, 0}, {1, 0, 0, 1}} 有面积为 3 和 1 的两座岛，返回 3。

using AreaGrid = std::vector<std::vector<int>>;
int area(AreaGrid& grid,int row,int col){
    int rows = grid.size();
    int cols = grid[0].size();
    if(row < 0 || row >= rows || col <0 || col >= cols){
        return 0;
    }
    if(grid[row][col] == 0){
        return 0;
    }
    grid[row][col] = 0;
    int total = 1;
    total += area(grid,row+1,col);
    total += area(grid,row-1,col);
    total += area(grid,row,col+1);
    total += area(grid,row,col-1);
    return total;
}
int maxAreaOfIsland(AreaGrid grid) {
    if(grid.empty() ||grid[0].empty()){
        return 0;
    }
    int best = 0;
    for(int row = 0;row < grid.size();row++){
        for(int col = 0; col <grid[0].size();col++){
            if(grid[row][col] == 1){
                best = std::max(best,area(grid,row,col));
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
