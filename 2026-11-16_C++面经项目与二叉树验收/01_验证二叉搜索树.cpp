#include <cassert>
#include <climits>

// 第 1 题：验证二叉搜索树（LeetCode 98，Medium，复测）。
// 左子树所有节点的值都严格小于根，右子树所有节点的值都严格大于根；
// 每棵子树也必须满足同样的条件。空树是有效的，不允许重复值。
//
//      2              5
//     / \            / \
//    1   3          1   4
//                      / \
//                     3   6
//   返回 true       返回 false：3 在 5 的右子树，但小于 5。
// 可以使用自己熟悉的方法；写完后解释时间和空间复杂度。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int v) : val(v) {}
};

// 可以自行添加辅助函数。
bool midreverse(TreeNode* root, TreeNode*& previous){
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
    TreeNode same(2); a.left = &same;
    assert(!isValidBST(&a));
    TreeNode lo(INT_MIN), hi(INT_MAX);
    lo.right = &hi;
    assert(isValidBST(&lo));
    TreeNode one(-3);
    assert(isValidBST(&one));
}
