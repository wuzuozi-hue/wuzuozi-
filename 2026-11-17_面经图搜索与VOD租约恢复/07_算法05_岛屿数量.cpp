#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

// 第 5 题：岛屿数量（Medium）
// '1' 是陆地，'0' 是水。上下左右连起来的陆地算同一个岛。
// 斜着相邻不算连通。返回岛屿的总数，空网格返回 0。
//
// 示例原图       标记每块岛屿
// 1 1 0         A A .
// 1 0 1         A . B
// 0 1 1         . B B
// A 和 B 各是一个岛，所以返回 2。

using Grid = std::vector<std::vector<char>>;
void sink(Grid& Grid,int row,int col){
    int rows = static_cast<int>(Grid.size());
    int cols = static_cast<int>(Grid[0].size());
    if(row < 0 ||row >= rows || col >= cols || col <0){
        return;
    }
    if(Grid[row][col] !='1'){
        return;
    }
    Grid[row][col] = '0';
    sink(Grid,row,col + 1);
    sink(Grid,row,col - 1);
    sink(Grid,row + 1,col);
    sink(Grid,row - 1,col);
}
int numIslands(Grid grid) {
    // 在这里实现。grid 按值传入，可以修改这份副本。
    if(grid.empty() || grid[0].empty()){
        return 0;
    }
    int rows = static_cast<int>(grid.size());
    int cols = static_cast<int>(grid[0].size());
    int count = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if(grid[row][col] == '1') {
                count++;
                sink(grid,row,col);
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
