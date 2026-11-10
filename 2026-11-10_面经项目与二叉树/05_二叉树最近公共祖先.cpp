#include <cassert>

// 第 4 题：二叉树的最近公共祖先（LeetCode 236，Medium）。
// p 和 q 是树中的两个不同节点，返回它们的最近公共祖先。
// 节点可以是自己的祖先；比较节点地址，不是比较 val。
//
//         3
//       /   \  
//      5     1
//     / \  
//    6   2
// p=5, q=1 返回 3；p=5, q=2 返回 5。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr){
        return nullptr;
    }
    if(root == p ||root== q){
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left,p,q);
    TreeNode* right = lowestCommonAncestor(root->right,p,q);
    if(left != nullptr &&right !=nullptr){
        return root;
    }
    if(left == nullptr){
        return right;
    }else{
        return left;
    }
}

int main() {
    TreeNode a(3), b(5), c(1), d(6), e(2);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e;
    assert(lowestCommonAncestor(&a, &b, &c) == &a);
    assert(lowestCommonAncestor(&a, &b, &e) == &b);
    assert(lowestCommonAncestor(&a, &d, &e) == &b);
    assert(lowestCommonAncestor(nullptr, &b, &c) == nullptr);
}
