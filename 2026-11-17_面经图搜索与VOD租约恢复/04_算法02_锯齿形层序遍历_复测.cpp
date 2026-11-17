#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
// 第 2 题：二叉树的锯齿形层序遍历（Medium，复测）
// 给定二叉树的根节点 root，返回每一层的节点值。
// 第 1 层从左到右，第 2 层从右到左，第 3 层从左到右，以此类推。
// 空树返回空结果。
// 示例：根为 3，左右子节点为 9、20，20 的左右子节点为 15、7。
// 返回 {{3}, {20, 9}, {15, 7}}。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int value) : val(value) {}
};
//std::vector<std::vector<int>> sum(TreeNode*root, std::vector<std::vector<int>> &result
std::vector<std::vector<int>> zigzagLevelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if(root == nullptr){
        return result;
    }
    std::queue <TreeNode*> q;
    q.push(root);
    int high = 1;
    while(!q.empty()){
        std::vector<int> level;
        int n = q.size();
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
    high++;
    }
    return result;
}

int main() {
    TreeNode a(3), b(9), c(20), d(15), e(7);
    a.left = &b;
    a.right = &c;
    c.left = &d;
    c.right = &e;
    assert(zigzagLevelOrder(nullptr).empty());
    assert((zigzagLevelOrder(&a) == std::vector<std::vector<int>>{{3}, {20, 9}, {15, 7}}));

    TreeNode f(1), g(2), h(3), i(4), j(5), k(6), l(7);
    f.left = &g;
    f.right = &h;
    g.right = &i;
    h.left = &j;
    i.left = &k;
    j.right = &l;
    assert((zigzagLevelOrder(&f) == std::vector<std::vector<int>>{{1}, {3, 2}, {4, 5}, {7, 6}}));

    TreeNode solo(8);
    assert((zigzagLevelOrder(&solo) == std::vector<std::vector<int>>{{8}}));
    std::cout << "Zigzag level order: all checks passed\n";
}
