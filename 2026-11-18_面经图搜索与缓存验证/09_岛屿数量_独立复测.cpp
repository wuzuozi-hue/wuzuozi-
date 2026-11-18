#include <cassert>
#include <iostream>
#include <vector>

// 200. 岛屿数量
// '1' 是陆地，'0' 是水。上下左右相连的陆地属于同一座岛。
// 返回网格中的岛屿数。grid 按值传入，可以修改这份副本。
// 示例 {{'1', '0'}, {'0', '1'}} 有两座岛。

using Grid = std::vector<std::vector<char>>;
void num(Grid& grid, int row,int col){
    int rows = grid.size();
    int cols = grid[0].size();
    if(col <0 || col >=cols || row <0 ||row>= rows){
        return;
    }
    if(grid[row][col] == '0'){
        return;
    }
    grid[row][col] = '0';
    num(grid,row+1,col);
    num(grid,row-1,col);
    num(grid,row,col+1);
    num(grid,row,col-1);
}
int numIslands(Grid grid) {
    if(grid.empty() || grid[0].empty()){
        return 0;
    }
    int count = 0;
    for(int row = 0;row<grid.size();row++){
        for(int col = 0; col <grid[0].size();col++){
            if(grid[row][col] == '1'){
                ++count;
                num(grid,row,col);
            }
        }
    }
    return count;
}

int main() {
    assert(numIslands({}) == 0);
    assert(numIslands({{'0', '0'}, {'0', '0'}}) == 0);
    assert(numIslands({{'1'}}) == 1);
    assert(numIslands({{'1', '0'}, {'0', '1'}}) == 2);
    assert(numIslands({{'1', '1', '0'}, {'1', '0', '1'}, {'0', '1', '1'}}) == 2);
    assert(numIslands({{'1', '1', '1'}, {'1', '0', '1'}, {'1', '1', '1'}}) == 1);
    assert(numIslands({{'1', '0', '1'}, {'0', '0', '0'}, {'1', '0', '1'}}) == 4);

    std::cout << "Number of islands: all checks passed\n";
}
