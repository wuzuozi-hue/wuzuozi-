#include <cassert>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

// 第 4 题：图像渲染（Easy）
// image 是非空矩形网格，(sr, sc) 是有效的起点，坐标从 0 开始。
// 把起点及所有与它四方向连通且颜色与起点原色相同的格子改成 color。
// 四方向是上、下、左、右，斜对角不算相邻。返回染色后的图像。
// 例如 image = {{1, 1, 0}, {1, 0, 1}}, 起点 (0, 0)，新颜色 2。
// 返回 {{2, 2, 0}, {2, 0, 1}}。右下角的 1 无法沿同色格子走到。

std::vector<std::vector<int>> floodFill(std::vector<std::vector<int>> image,
                                        int sr, int sc, int color) {
    int oldcolor = image[sr][sc];
    if(oldcolor == color)
    return image;
    std::queue<std::pair<int,int>> q;
    image[sr][sc] = color;
    q.emplace(sr,sc);
    int cols = static_cast<int>(image[0].size());
    int rows =static_cast<int>(image.size());
    int dr[] = {0,0,-1,1};
    int dc[] = {1,-1,0,0};
    while(!q.empty()){
        auto cell = q.front();
        q.pop();
        int row = cell.first;
        int col = cell.second;
        int nextcol = col+1;
        if(nextcol < cols && image[row][nextcol] == oldcolor){
                image[row][col+1] = color;
                q.emplace(row,col+1);
        }
    }

    return image;
}

int main() {
    using Grid = std::vector<std::vector<int>>;

    assert((floodFill({{1, 1, 0}, {1, 0, 1}}, 0, 0, 2) ==
            Grid{{2, 2, 0}, {2, 0, 1}}));
    assert((floodFill({{1, 0}, {0, 1}}, 0, 0, 3) ==
            Grid{{3, 0}, {0, 1}}));
    assert((floodFill({{8, 8}, {8, 8}}, 1, 1, 8) ==
            Grid{{8, 8}, {8, 8}}));
    assert((floodFill({{0}}, 0, 0, 4) == Grid{{4}}));
    assert((floodFill({{2, 1, 1, 1}}, 0, 2, 7) == Grid{{2, 7, 7, 7}}));
    assert((floodFill({{1, 1, 0}, {1, 1, 0}, {0, 1, 1}}, 1, 1, 4) ==
            Grid{{4, 4, 0}, {4, 4, 0}, {0, 4, 4}}));

    std::cout << "Flood fill: all checks passed\n";
}
