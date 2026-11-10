#include <cassert>

// 第 7 题：合并二叉树（LeetCode 617，Easy，复测）。
// 两个对应节点都存在时，结果节点值为两者之和；仅有一个时保留该节点。
// 本题可以修改并复用第一棵树的节点，不要求新建整棵树。
//
//      1       2          3
//     /       / \        / \ 
//    3       1   3      4   3
//                 
// 第一棵和第二棵树合并后，得到右侧的树。
// 两棵都是空树时返回 nullptr。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* mergeTrees(TreeNode* a, TreeNode* b) {
    if(a == nullptr && b == nullptr){
        return nullptr;
    }
    if(a !=nullptr && b == nullptr){
        return a;
    }
    if(b!=nullptr && a == nullptr){
        return b;
    }
    TreeNode* result = new TreeNode(a->val + b->val);
    result->left = mergeTrees(a->left,b->left);
    result->right = mergeTrees(a->right,b->right);
    return result;
}

int main() {
    assert(mergeTrees(nullptr, nullptr) == nullptr);
    TreeNode a(1), leftA(3), b(2), leftB(1), rightB(3);
    a.left=&leftA; b.left=&leftB; b.right=&rightB;
    TreeNode* root=mergeTrees(&a, &b);
    assert(root && root->val == 3);
    assert(root->left && root->left->val == 4);
    assert(root->right && root->right->val == 3);
    TreeNode* only=mergeTrees(nullptr, &b);
    assert(only && only->val == b.val);
}
