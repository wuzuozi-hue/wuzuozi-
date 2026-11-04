#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

void preorder(TreeNode* root, std::vector<int>& result) {
    // 递归实现：先当前节点，再左子树，最后右子树。
    if(root == nullptr){
        return ;
    } 
    result.push_back(root->val);
    preorder(root ->left,result);
    preorder(root ->right,result);
}

void check(const char* name, TreeNode* root, const std::vector<int>& expected) {
    std::vector<int> result;
    preorder(root, result);
    std::cout << name << ": " << (result == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    TreeNode a(1), b(2), c(3), d(4);
    check("single", &a, {1});
    a.left = &b; a.right = &c; b.right = &d;
    check("branching", &a, {1, 2, 4, 3});
    check("right child", &b, {2, 4});
}
