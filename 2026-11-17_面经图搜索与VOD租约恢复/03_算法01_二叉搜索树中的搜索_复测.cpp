#include <cassert>
#include <iostream>

// 第 1 题：二叉搜索树中的搜索（Easy，复测）
// 给定二叉搜索树的根节点 root 和整数 val，返回树中值为 val 的原节点指针。
// 找不到时返回 nullptr。不要新建节点，也不要修改原树。
//
//         5
//        / \
//       2   9
//        \  /
//         4 7
// 示例：val = 7 返回指向原节点 7 的指针；val = 3 返回 nullptr。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int value) : val(value) {}
};

TreeNode* searchBST(TreeNode* root, int val) {
    // 在这里实现。
    if(root == nullptr){
        return nullptr;
    }
    if(root->val == val){
        return root;
    }
    if(root->val < val){
        return searchBST(root->right,val);
    }
    return searchBST(root->left,val);
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
