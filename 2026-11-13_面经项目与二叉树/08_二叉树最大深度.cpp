#include <cassert>
#include <algorithm>

// 第 8 题：二叉树的最大深度（LeetCode 104，Easy，复测）。
// 返回从根节点到最远叶子节点的路径上的节点数。空树深度为 0。
//
//          3
//         / \
//        9  20
//          /  \
//         15   7
// 最大深度为 3，例如路径 3 -> 20 -> 15。
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
int depth(TreeNode* root,int& best){
    if(root == nullptr){
        return 0;
    }
    int leftdepth = depth(root->left,best);
    int rightdepth = depth(root->right,best);
    best = std::max(best,leftdepth+rightdepth);
    return std::max(leftdepth,rightdepth)+1;
}
int maxDepth(TreeNode* root) { 
    int best =0;
    return depth(root,best);
}

int main() {
    assert(maxDepth(nullptr) == 0);
    TreeNode a(3), b(9), c(20), d(15), e(7);
    a.left=&b; a.right=&c; c.left=&d; c.right=&e;
    assert(maxDepth(&a) == 3);
    assert(maxDepth(&b) == 1);
    TreeNode x(1), y(2), z(3), w(4);
    x.left=&y; y.left=&z; z.left=&w;
    assert(maxDepth(&x) == 4);
}
