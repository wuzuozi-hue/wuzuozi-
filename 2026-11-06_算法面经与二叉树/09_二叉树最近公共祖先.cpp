#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
// p、q 是树中两个不同的节点，比较节点地址，返回最近公共祖先。
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr || root ==p || root == q){
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left,p,q);
    TreeNode* right =lowestCommonAncestor(root->right,p,q);
    if(left !=nullptr &&right!=nullptr){
        return root;
    }
    if(left !=nullptr){
        return left;
    }
    return right;
}

void check(const char* name, TreeNode* actual, TreeNode* expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    TreeNode a(3), b(5), c(1), d(6), e(2), f(7), g(4);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e; e.left=&f; e.right=&g;
    check("across branches", lowestCommonAncestor(&a, &b, &c), &a);
    check("node is ancestor", lowestCommonAncestor(&a, &b, &g), &b);
    check("inside subtree", lowestCommonAncestor(&a, &f, &g), &e);
    check("same branch", lowestCommonAncestor(&a, &d, &g), &b);
}
