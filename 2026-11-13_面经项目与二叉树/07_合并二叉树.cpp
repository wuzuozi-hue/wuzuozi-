#include <cassert>

// 第 7 题：合并二叉树（LeetCode 617，Easy，复测）。
// 对两棵树对应位置：都有节点则节点值相加；只有一棵有节点则保留该节点。
// 返回合并后的根节点。可以直接修改并复用 a 或 b 的节点，不必新建整棵树。
//
//       1          2              3
//      / \        / \            / \
//     3   2      1   3    =>    4   5
//    /            \   \        / \   \
//   5              4   7      5   4   7
//
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* mergeTrees(TreeNode* a, TreeNode* b) {
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    TreeNode* result = new TreeNode(a->val + b->val);
    result->left= mergeTrees(a->left,b->left);
    result->right= mergeTrees(a->right,b->right);
    return result;
}

int main() {
    assert(mergeTrees(nullptr, nullptr) == nullptr);
    TreeNode a(1), b(3), c(2), d(5);
    a.left=&b; a.right=&c; b.left=&d;
    TreeNode x(2), y(1), z(3), w(4), v(7);
    x.left=&y; x.right=&z; y.right=&w; z.right=&v;
    TreeNode* r = mergeTrees(&a, &x);
    assert(r && r->val==3 && r->left && r->left->val==4 && r->right && r->right->val==5);
    assert(r->left->left && r->left->left->val==5);
    assert(r->left->right && r->left->right->val==4);
    assert(r->right->right && r->right->right->val==7);
    TreeNode single(-3);
    TreeNode* t = mergeTrees(nullptr, &single);
    assert(t && t->val == -3);
}
