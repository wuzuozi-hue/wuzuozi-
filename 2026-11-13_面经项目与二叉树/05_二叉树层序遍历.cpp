#include <cassert>
#include <queue>
#include <vector>

// 第 5 题：二叉树的层序遍历（LeetCode 102，Medium，复测）。
// 按从上到下、每层从左到右的顺序，返回各层节点值；空树返回空数组。
//
//          3
//         / \
//        9  20
//          /  \
//         15   7
// 返回 {{3}, {9,20}, {15,7}}。
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if(root == nullptr){
        return result;
    }
    std::queue <TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        std::vector<int> level;
        int n = q.size();
        for(int i =0;i<n;i++){
            TreeNode* cur = q.front();
            q.pop();
            if(cur->left != nullptr){
                q.push(cur->left);
            }
            if(cur->right != nullptr){
                q.push(cur->right);
            }
            level.push_back(cur->val);
        }
    result.push_back(level);
    }
    return result;
}

int main() {
    assert(levelOrder(nullptr).empty());
    TreeNode a(3), b(9), c(20), d(15), e(7);
    a.left=&b; a.right=&c; c.left=&d; c.right=&e;
    assert((levelOrder(&a) == std::vector<std::vector<int>>{{3},{9,20},{15,7}}));
    assert((levelOrder(&b) == std::vector<std::vector<int>>{{9}}));
    TreeNode x(-1), y(0); x.right=&y;
    assert((levelOrder(&x) == std::vector<std::vector<int>>{{-1},{0}}));
}
