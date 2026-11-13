#include <cassert>
#include <utility>
// 第 9 题：翻转二叉树（LeetCode 226，Easy，新题）。
// 将每个节点的左右子树交换，返回翻转后的根节点。空树返回 nullptr。
// 可以直接修改原树。
//
//       4                4
//      / \              / \
//     2   7    翻转后   7   2
//    / \ / \          / \ / \
//   1  3 6  9        9  6 3  1
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr){
        return nullptr;
    }
    std::swap(root->left,root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

int main() {
    assert(invertTree(nullptr) == nullptr);
    TreeNode a(4), b(2), c(7), d(1), e(3), f(6), g(9);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e; c.left=&f; c.right=&g;
    TreeNode* r = invertTree(&a);
    assert(r && r->val==4 && r->left && r->left->val==7 && r->right && r->right->val==2);
    assert(r->left->left && r->left->left->val==9);
    assert(r->left->right && r->left->right->val==6);
    assert(r->right->left && r->right->left->val==3);
    assert(r->right->right && r->right->right->val==1);
    TreeNode single(-1);
    TreeNode* one = invertTree(&single);
    assert(one && one->val == -1 && !one->left && !one->right);
}
