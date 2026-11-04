#include <algorithm>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

int maxDepth(TreeNode* root) {
    if(root == nullptr){
        return 0;
    }
    int leftdepth = maxDepth(root->left);
    int rightdepth = maxDepth(root->right);
    return std::max(leftdepth,rightdepth) + 1;
}

void check(const char* name, int actual, int expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", maxDepth(nullptr), 0);
    TreeNode a(1), b(2), c(3), d(4);
    check("single", maxDepth(&a), 1);
    a.left = &b; a.right = &c; b.left = &d;
    check("unbalanced", maxDepth(&a), 3);
    check("leaf", maxDepth(&c), 1);
}
