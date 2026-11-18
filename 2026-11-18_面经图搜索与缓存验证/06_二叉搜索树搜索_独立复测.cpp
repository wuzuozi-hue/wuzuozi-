#include <cassert>
#include <iostream>

// 700. 二叉搜索树中的搜索
// 给定树根 root 和整数 val，返回值等于 val 的原节点指针。
// 找不到时返回 nullptr。不要修改树或创建新节点。
//
//         5
//        / \
//       2   9
//        \  /
//         4 7
// val = 7 时返回节点 7，val = 3 时返回 nullptr。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int value) : val(value) {}
};

TreeNode* searchBST(TreeNode* root, int val) {
    if(root == nullptr){
        return nullptr;
    }
    if(root->val == val){
        return root;
    }
    if(root->val < val){
        return searchBST(root->right,val);
    }
    if(root->val >val){
        return searchBST(root->left,val);
    }
}

int main() {
    TreeNode root(5), left(2), right(9), leftRight(4), rightLeft(7);
    root.left = &left;
    root.right = &right;
    left.right = &leftRight;
    right.left = &rightLeft;

    assert(searchBST(nullptr, 5) == nullptr);
    assert(searchBST(&root, 5) == &root);
    assert(searchBST(&root, 2) == &left);
    assert(searchBST(&root, 4) == &leftRight);
    assert(searchBST(&root, 7) == &rightLeft);
    assert(searchBST(&root, 9) == &right);
    assert(searchBST(&root, 3) == nullptr);
    assert(searchBST(&root, 10) == nullptr);

    std::cout << "BST search: all checks passed\n";
}
