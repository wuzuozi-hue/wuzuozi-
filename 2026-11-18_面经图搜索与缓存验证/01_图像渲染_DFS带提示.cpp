#include <cassert>
#include <iostream>
#include <vector>

// 图像渲染：从起点出发，只沿上、下、左、右穿过与起点原色相同的格子。
// 给所有走到的格子换颜色。图像非空，起点一定在图像内。
//
// 起点在 (0, 0)，把连通的 1 换成 2：
//         第 0 列  第 1 列  第 2 列
// 第 0 行   ★1  ───→  1        0
//            │
// 第 1 行    1        0        1   ← 走不到，保留 1
//
// 预期结果 {{2, 2, 0}, {2, 0, 1}}。
// 练习顺序：先从 (0, 0) 手推越界和非原色的格子，再填 paint 中的 TODO。

using Grid = std::vector<std::vector<int>>;

void paint(Grid& image, int row, int col, int oldColor, int newColor) {
    const int rows = static_cast<int>(image.size());
    const int cols = static_cast<int>(image[0].size());

    // TODO 1：坐标越界就返回；然后再读取格子，颜色不对也返回。
    if(row <0 || row >= rows || col <0 ||col >= cols){
        return;
    }
    if(image[row][col] != oldColor){
        return ;
    }
    // TODO 2：把当前格子染成新颜色。为什么要在递归处理邻居之前染？
    image[row][col] = newColor;
    // TODO 3：先写「去右边」的递归调用，再补其他三个方向。
    paint(image,row+1,col,oldColor,newColor);
    paint(image,row-1,col,oldColor,newColor);
    paint(image,row,col+1,oldColor,newColor);
    paint(image,row,col-1,oldColor,newColor);
}

Grid floodFill(Grid image, int sr, int sc, int color) {
    // TODO 4：记录起点原色。若和目标色一样，直接返回；否则从起点调用 paint
    int oldcolor = image[sr][sc];
    if(oldcolor == color){
        return image;
    }
    paint(image,sr,sc,oldcolor,color);
    return image;
}

int main() {
    assert((floodFill({{1, 1, 0}, {1, 0, 1}}, 0, 0, 2) ==
            Grid{{2, 2, 0}, {2, 0, 1}}));
    assert((floodFill({{1, 0}, {0, 1}}, 0, 0, 3) == Grid{{3, 0}, {0, 1}}));
    assert((floodFill({{8, 8}, {8, 8}}, 1, 1, 8) == Grid{{8, 8}, {8, 8}}));
    assert((floodFill({{0}}, 0, 0, 4) == Grid{{4}}));
    assert((floodFill({{2, 1, 1, 1}}, 0, 2, 7) == Grid{{2, 7, 7, 7}}));
    assert((floodFill({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, 1, 1, 6) ==
            Grid{{6, 6, 6}, {6, 6, 6}, {6, 6, 6}}));

    std::cout << "Flood fill DFS: all checks passed\n";
}
