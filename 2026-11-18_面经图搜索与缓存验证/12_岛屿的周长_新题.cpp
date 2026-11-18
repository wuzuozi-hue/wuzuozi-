#include <cassert>
#include <iostream>
#include <vector>

// 463. 岛屿的周长
// 1 表示陆地，0 表示水。求陆地与水或网格外相邻的边数。
// 两格陆地共用的边不算周长。{{1}} 的周长为 4，{{1, 1}} 的周长为 6。
// 本练习也允许空网格和全水网格，它们的周长为 0。

using Grid = std::vector<std::vector<int>>;
// int sum(Grid& grid,int row,int col){
//     int rows = grid.size();
//     int cols = grid[0].size();
//     if(row < 0|| row>= rows || col <0 || col >= cols){
//         return 0;
//     }
//     if(grid[row][col] == 0){
//         return ;
//     }

//     sum(grid,row+1,col);
//     sum(grid,row-1,col);
//     sum(grid,row,col+1);
//     sum(grid,row,col-1);

// }
int islandPerimeter(const Grid& grid) {
    if(grid.empty()|| grid[0].empty()){
        return 0;
    }
    const int rows = static_cast<int>(grid.size());
    const int cols = static_cast<int>(grid[0].size());
    int perimeter = 0;
    for(int row = 0;row<grid.size();row++){
        for(int col = 0;col < grid[0].size();col++){
            if(grid[row][col] == 0){
                continue;
            }
            if(col +1 == cols || grid[row][col+1] == 0){
                ++perimeter;
            }
            if(col -1 < 0 || grid[row][col-1] == 0){
                ++perimeter;
            }
            if(row +1 == rows || grid[row+1][col] == 0){
                ++perimeter;
            }
            if(row -1 < 0 || grid[row-1][col] == 0){
                ++perimeter;
            }
        }
    }
    return perimeter;
}

int main() {
    assert(islandPerimeter({}) == 0);
    assert(islandPerimeter({{0, 0}, {0, 0}}) == 0);
    assert(islandPerimeter({{1}}) == 4);
    assert(islandPerimeter({{1, 1}}) == 6);
    assert(islandPerimeter({{1, 0}}) == 4);
    assert(islandPerimeter({{1, 1}, {1, 1}}) == 8);
    assert(islandPerimeter({{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}}) == 16);
    std::cout << "Island perimeter: all checks passed\n";
}
