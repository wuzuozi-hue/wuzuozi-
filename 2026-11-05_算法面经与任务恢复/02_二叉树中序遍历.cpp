#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

void inorder(TreeNode* root, std::vector<int>& result) {
    // 中序遍历：左子树 -> 当前节点 -> 右子树。
    if(root == nullptr){
        return ;
    }
    inorder(root->left,result);
    result.push_back(root->val);
    inorder(root->right,result);
}

void check(const char* name, TreeNode* root, const std::vector<int>& expected) {
    std::vector<int> actual;
    inorder(root, actual);
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    TreeNode a(1), b(2), c(3), d(4);
    check("single", &a, {1});
    a.left = &b; a.right = &c; b.right = &d;
    check("branching", &a, {2, 4, 1, 3});
    check("right child", &b, {2, 4});
}
