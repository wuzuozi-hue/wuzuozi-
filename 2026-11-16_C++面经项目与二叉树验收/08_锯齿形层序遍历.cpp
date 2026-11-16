#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

// 第 8 题：二叉树的锯齿形层序遍历（LeetCode 103，Medium）。
// 第一层从左到右，第二层从右到左，第三层又从左到右，依次交替。
// 按层返回节点值；空树返回空数组。
//
//          3
//         / \
//        9  20
//          /  \
//         15   7
// 返回 {{3}, {20, 9}, {15, 7}}。
// 示例二：只有根节点 1 时返回 {{1}}。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if(root == nullptr){
        return result;
    }
    std::queue <TreeNode*> q;
    q.push(root);
    int high = 1;
    while(!q.empty()){
        int n = q.size();
        std::vector<int> level;
        for(int i =0;i<n;i++){
            TreeNode* cur = q.front();
            q.pop();
            level.push_back(cur->val);
            if(cur->left !=nullptr){
                q.push(cur->left);
            }
            if(cur->right !=nullptr){
                q.push(cur->right);
            }
        }
        if(high % 2 == 0){
            std::reverse(level.begin(),level.end());
        }

        result.push_back(level);
        ++high;
    }
    return result;
}

int main() {
    assert(zigzagLevelOrder(nullptr).empty());
    TreeNode a(3), b(9), c(20), d(15), e(7), f(1), g(2);
    assert((zigzagLevelOrder(&a) == std::vector<std::vector<int>>{{3}}));
    a.left=&b; a.right=&c; c.left=&d; c.right=&e;
    assert((zigzagLevelOrder(&a) == std::vector<std::vector<int>>{{3},{20,9},{15,7}}));
    d.left=&f; e.right=&g;
    assert((zigzagLevelOrder(&a) == std::vector<std::vector<int>>{{3},{20,9},{15,7},{2,1}}));
}
