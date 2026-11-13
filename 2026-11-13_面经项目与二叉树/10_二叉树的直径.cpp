#include <cassert>
#include <algorithm>

// 第 10 题：二叉树的直径（LeetCode 543，Easy，复测）。
// 返回树中任意两个节点之间最长路径的长度，以边数计数。
// 最长路径不一定经过根节点；空树和只有一个节点的树，直径为 0。
//
//          1
//         / \
//        2   3
//       / \
//      4   5
// 直径为 3，例如路径 4 -> 2 -> 1 -> 3，共 3 条边。
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
int depth(TreeNode* root,int& maxdepth){
    if(root == nullptr){
        return 0;
    }
    int leftdepth =depth(root->left,maxdepth);
    int rightdepth =depth(root->right,maxdepth);
    maxdepth = std::max(maxdepth,leftdepth+rightdepth);
    return std::max(leftdepth,rightdepth) +1;
}
int diameterOfBinaryTree(TreeNode* root) {
    int maxdepth = 0;
    depth(root,maxdepth);
    return maxdepth;
}

int main() {
    assert(diameterOfBinaryTree(nullptr) == 0);
    TreeNode a(1), b(2), c(3), d(4), e(5);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e;
    assert(diameterOfBinaryTree(&a) == 3);
    assert(diameterOfBinaryTree(&d) == 0);
    TreeNode x(0), y(1), z(2), u(3), v(4), w(5);
    x.left=&y; y.left=&z; y.right=&u; z.left=&v; u.right=&w;
    assert(diameterOfBinaryTree(&x) == 4);
}
