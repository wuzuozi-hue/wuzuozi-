#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
bool midreverse(TreeNode* root,TreeNode* &previous){
    if(root == nullptr ){
        return true;
    }
    if(!midreverse(root->left,previous)){
        return false;
    }
    if(previous != nullptr && root ->val <= previous->val){
        return false;
    }
    previous = root;
    return midreverse(root->right,previous);
}

// 每个节点的左子树所有值都严格小于它，右子树所有值都严格大于它。
bool isValidBST(TreeNode* root) {
    TreeNode* previous = nullptr;
    return midreverse(root,previous);
}

void check(const char* name, bool actual, bool expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", isValidBST(nullptr), true);
    TreeNode a(5), b(2), c(8), d(1), e(4), f(6), g(9);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e; c.left=&f; c.right=&g;
    check("valid", isValidBST(&a), true);
    TreeNode h(5), i(2), j(8), k(4);
    h.left=&i; h.right=&j; j.left=&k;
    check("ancestor violation", isValidBST(&h), false);
    TreeNode l(2), m(2);
    l.left=&m;
    check("duplicate", isValidBST(&l), false);
}
