#include <cassert>

// 第 2 题：验证二叉搜索树（LeetCode 98，Medium）
// 每个节点的左子树所有值都小于它，右子树所有值都大于它。
// 不允许重复值；空树算有效。
//
// 有效：     2       无效：    5
//           / \               / \
//          1   3             1   4
//                               / \
//                              3   6
// 右子树中有 3，小于根节点 5，所以第二棵树无效。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 这题是带提示复测：中序遍历的值必须严格递增。
// 你可以定义辅助函数，并用 previous 记录上一个访问的节点。
bool midreverse(TreeNode*root, TreeNode*& previous){
    if(root == nullptr){
        return true;
    }

    if(!midreverse(root->left,previous)){
        return false;
    }
    if(previous !=nullptr && previous->val >=root->val)
    return false;

    previous = root;
    return midreverse(root->right,previous);

}
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
    TreeNode x(2), y(2);
    x.left = &y;
    assert(!isValidBST(&x));
}
