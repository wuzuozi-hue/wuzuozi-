#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 将每个节点的左右子树交换，返回翻转后的根节点。
TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr){
        return nullptr;
    }
    std::swap(root->left,root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

void check(const char* name, bool passed) {
    std::cout << name << ": " << (passed ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", invertTree(nullptr) == nullptr);
    TreeNode a(1), b(2), c(3), d(4);
    check("single", invertTree(&a) == &a && a.left == nullptr && a.right == nullptr);
    a.left = &b; a.right = &c; b.right = &d;
    TreeNode* result = invertTree(&a);
    check("root and branches", result == &a && a.left == &c && a.right == &b && b.left == &d && b.right == nullptr);
    invertTree(&a);
    check("invert twice", a.left == &b && a.right == &c && b.right == &d && b.left == nullptr);
}
