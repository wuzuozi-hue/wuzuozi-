#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 236（Mid，复测）
// 给定一棵普通二叉树以及其中两个不同节点 p、q，返回它们的最近公共祖先。
// 节点可以是自己的祖先；p、q 一定存在于树中；比较节点地址，不比较值。
//          3
//       /     \
//      5       1
//     / \     / \
//    6   2   0   8
//       / \
//      7   4
// p=5, q=1 返回 3；p=5, q=4 返回 5。
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr){
        return nullptr;
    }
    TreeNode* left = lowestCommonAncestor(root->left,p,q);
    TreeNode* right =lowestCommonAncestor(root->right,p,q);
    if(root == q || root ==p){
        return root;
    }
    if(left !=nullptr &&right !=nullptr){
        return root;
    }
    if(left!=nullptr ){
        return left;
    }
    if(right != nullptr){
        return right;
    }
   return nullptr;
    
}

int main() {
    TreeNode n7(7), n4(4), n2(2, &n7, &n4), n6(6), n5(5, &n6, &n2);
    TreeNode n0(0), n8(8), n1(1, &n0, &n8), n3(3, &n5, &n1);
    int failed = 0;
    auto check = [&](const char* name, TreeNode* p, TreeNode* q, TreeNode* expected) {
        bool ok = lowestCommonAncestor(&n3, p, q) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) ++failed;
    };
    check("opposite branches", &n5, &n1, &n3);
    check("node is ancestor", &n5, &n4, &n5);
    check("siblings", &n7, &n4, &n2);
    check("root is target", &n3, &n8, &n3);
    check("same subtree", &n6, &n4, &n5);
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
