#include <cassert>
#include <climits>

// 第 3 题：验证二叉搜索树（LeetCode 98，Medium，复测）。
// 判断一棵树是否为二叉搜索树：每个节点的左子树所有值都小于该节点，
// 右子树所有值都大于该节点；所有子树也必须满足。空树返回 true。
//
// 有效：    2           无效：    5
//          / \                  / \
//         1   3                1   4
//                                 / \
//                                3   6
// 第二棵树中 4 在 5 的右子树，但 4 < 5，故返回 false。
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
bool midreverse(TreeNode*root, TreeNode*& previous){
    if(root == nullptr){
        return true;
    }

    if(!midreverse(root->left,previous)){
        return false;
    }
    if(previous != nullptr && previous->val >= root->val){
        return false;
    }
    previous = root;
    return midreverse(root->right,previous);
}
// 可自行添加辅助函数。
bool isValidBST(TreeNode* root) {
    TreeNode* previous = nullptr;
    return midreverse(root,previous);
}
int main() {
    assert(isValidBST(nullptr));
    TreeNode a(2), b(1), c(3);
    a.left=&b; a.right=&c;
    assert(isValidBST(&a));
    TreeNode d(5), e(1), f(4), g(3), h(6);
    d.left=&e; d.right=&f; f.left=&g; f.right=&h;
    assert(!isValidBST(&d));
    TreeNode duplicate(2); a.right=&duplicate;
    assert(!isValidBST(&a));
    TreeNode minimum(INT_MIN), maximum(INT_MAX);
    minimum.right=&maximum;
    assert(isValidBST(&minimum));
}
