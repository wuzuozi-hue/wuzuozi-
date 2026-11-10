#include <algorithm>
#include <cassert>

// 第 5 题：二叉树的直径（LeetCode 543，Easy）。
// 返回树中任意两个节点之间最长路径的长度，长度按边数计算。
// 路径不一定经过根节点；空树或单节点树的直径为 0。
//
//        1
//      /   \  
//     2     3
//    / \  
//   4   5
// 最长路径例如 4 -> 2 -> 1 -> 3，共 3 条边，返回 3。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
int maxdepth(TreeNode* root, int& best){
    if(root == nullptr){
        return 0;
    }
    int leftdepth = maxdepth(root->left,best);
    int rightdepth = maxdepth(root->right,best);
    best = std::max(best,leftdepth+rightdepth);
    return std::max(leftdepth,rightdepth) +1;
}
int diameterOfBinaryTree(TreeNode* root) {
    int best = 0;
    maxdepth(root,best);
    return best;
}

int main() {
    assert(diameterOfBinaryTree(nullptr) == 0);
    TreeNode a(1), b(2), c(3), d(4), e(5);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e;
    assert(diameterOfBinaryTree(&a) == 3);
    assert(diameterOfBinaryTree(&d) == 0);
    TreeNode x(1), y(2), z(3), w(4);
    x.right=&y; y.right=&z; z.right=&w;
    assert(diameterOfBinaryTree(&x) == 3);
}
