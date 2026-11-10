#include <cassert>
#include <queue>
#include <vector>

// 第 1 题：二叉树的层序遍历（LeetCode 102，Medium）
// 从上到下、从左到右逐层遍历，每层单独放进一个数组。
//
//       3
//      / \
//     9  20
//       /  \
//      15   7
// 返回 {{3}, {9, 20}, {15, 7}}；空树返回 {}。

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
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        std::vector<int> level;
        int n = q.size();
        for(int i =0;i<n;i++){
            TreeNode*cur = q.front();
            q.pop();
            level.push_back(cur->val);
            if(cur->left!=nullptr){
                q.push(cur->left);
            }
            if(cur->right!=nullptr){
                q.push(cur->right);
            }
        }
        result.push_back(level);
    }
    return result;
}

int main() {
    TreeNode a(3), b(9), c(20), d(15), e(7);
    a.left = &b; a.right = &c; c.left = &d; c.right = &e;
    assert((levelOrder(&a) == std::vector<std::vector<int>>{{3}, {9, 20}, {15, 7}}));
    assert(levelOrder(nullptr).empty());
    TreeNode single(5);
    assert((levelOrder(&single) == std::vector<std::vector<int>>{{5}}));
}
