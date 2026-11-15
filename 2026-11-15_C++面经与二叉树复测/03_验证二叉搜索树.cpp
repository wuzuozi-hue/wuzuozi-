#include <cassert>

// 第 3 题：验证二叉搜索树（LeetCode 98，Medium，复测）。
// 对每一个节点：左子树所有节点的值都必须小于它的值，
// 右子树所有节点的值都必须大于它的值；空树是有效的。
// 节点值可以为负数，不允许重复值。
//
//       2                 5
//      / \               / \
//     1   3             1   4
//                          / \
//                         3   6
//    返回 true          返回 false：3 在 5 的右子树，但小于 5

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
bool midreverse(TreeNode* root, TreeNode* &previous){
    if(root == nullptr){
        return true;
    }

    if(!midreverse(root->left,previous)){
        return false;
    }
    if(previous !=nullptr && previous->val >= root->val){
        return false;
    }
    previous = root;
    return midreverse(root->right,previous);
}
// 可以自行添加辅助函数。
bool isValidBST(TreeNode* root) {
    TreeNode* previous = nullptr;
    return midreverse(root,previous);
}

int main() {
    assert(isValidBST(nullptr));
    TreeNode a(2), b(1), c(3);
    a.left = &b; a.right = &c;
    assert(isValidBST(&a));
    TreeNode d(5), e(1), f(4), g(3), h(6);
    d.left = &e; d.right = &f; f.left = &g; f.right = &h;
    assert(!isValidBST(&d));
    TreeNode duplicate(2);
    a.left = &duplicate;
    assert(!isValidBST(&a));
    TreeNode single(-5);
    assert(isValidBST(&single));
}
