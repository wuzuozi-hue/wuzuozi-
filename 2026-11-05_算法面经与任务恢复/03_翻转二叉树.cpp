#include <algorithm>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr){
        return nullptr;
    }
    std::swap(root->left,root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

void check(const char* name, bool ok) {
    std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", invertTree(nullptr) == nullptr);
    TreeNode single(9);
    check("single", invertTree(&single) == &single && !single.left && !single.right);
    TreeNode a(1), b(2), c(3), d(4);
    a.left = &b; a.right = &c; b.left = &d;
    TreeNode* result = invertTree(&a);
    check("root and children", result == &a && a.left == &c && a.right == &b);
    check("deeper child", !b.left && b.right == &d);
}
