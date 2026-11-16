#include <cassert>

// 第 10 题：二叉搜索树的最近公共祖先（LeetCode 235，Medium）。
// 给定二叉搜索树 root 和其中两个不同节点 p、q，返回它们的最近公共祖先。
// 一个节点可以是自身的祖先。返回原树中的节点指针，不创建新节点。
// 保证 p、q 均存在于树中，节点值互不相同，且满足二叉搜索树性质。
//
//              6
//            /   \
//           2     8
//          / \   / \
//         0   4 7   9
//            / \
//           3   5
// p=2, q=8：返回节点 6。
// p=2, q=4：返回节点 2（节点本身可作为祖先）。

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
    if(q == nullptr && p!=nullptr){
        return p;
    }
    if(q!=nullptr && p == nullptr){
        return q;
    }
    if(root == p || root == q){
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left,p,q);
    TreeNode* right = lowestCommonAncestor(root->right,p,q);
    if(left != nullptr && right !=nullptr){
        return root;
    }
    if(left != nullptr){
        return left;
    }else{
        return right;
    }
}

int main() {
    TreeNode a(6), b(2), c(8), d(0), e(4), f(7), g(9), h(3), i(5);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e; c.left=&f; c.right=&g;
    e.left=&h; e.right=&i;
    assert(lowestCommonAncestor(&a, &b, &c) == &a);
    assert(lowestCommonAncestor(&a, &b, &e) == &b);
    assert(lowestCommonAncestor(&a, &h, &i) == &e);
    assert(lowestCommonAncestor(&a, &g, &f) == &c);
    assert(lowestCommonAncestor(&a, &d, &h) == &b);
}
