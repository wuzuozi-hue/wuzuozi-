#include <algorithm>
#include <cassert>

// 第 4 题：二叉树的直径（LeetCode 543，Easy，复测）。
// 直径是树中任意两个节点之间最长路径的边数；这条路径不一定经过根。
// 空树、只有一个节点的树，直径都是 0。
//
//       1
//      / \
//     2   3
//    / \
//   4   5
// 最长路径可为 4 -> 2 -> 1 -> 3，共 3 条边，返回 3。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
int depth(TreeNode* root, int&best){
    if(root == nullptr){
        return 0;
    }
    int leftdepth = depth(root->left,best);
    int rightdepth = depth(root->right,best);
    best = std::max(best, leftdepth+rightdepth);
    return std::max(leftdepth,rightdepth) +1;
}
// 可以自行添加辅助函数。
int diameterOfBinaryTree(TreeNode* root) {
    int best = 0;
    depth(root,best);
    return best;
}

int main() {
    assert(diameterOfBinaryTree(nullptr) == 0);
    TreeNode a(1), b(2), c(3), d(4), e(5);
    assert(diameterOfBinaryTree(&a) == 0);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e;
    assert(diameterOfBinaryTree(&a) == 3);
    TreeNode f(6), g(7), h(8), i(9);
    d.left=&f; f.left=&g; e.right=&h; h.right=&i;
    assert(diameterOfBinaryTree(&a) == 6); // g -> f -> d -> b -> e -> h -> i
}
