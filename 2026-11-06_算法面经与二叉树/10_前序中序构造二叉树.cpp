#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 两个遍历序列对应同一棵树，节点值互不相同；返回构造后的根节点。
TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    TreeNode* build(
        const std::vector<int>& pre,
        const std::vector<int>& in,
        int preleft,int preright,
        int inleft,int inright){
            if(preleft > preright){
                return nullptr;
            }
        
        };
    
}

void preorderOf(TreeNode* root, std::vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorderOf(root->left, result);
    preorderOf(root->right, result);
}
void inorderOf(TreeNode* root, std::vector<int>& result) {
    if (!root) return;
    inorderOf(root->left, result);
    result.push_back(root->val);
    inorderOf(root->right, result);
}
void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left); destroy(root->right); delete root;
}
void check(const char* name, const std::vector<int>& pre, const std::vector<int>& in) {
    TreeNode* root = buildTree(pre, in);
    std::vector<int> actualPre, actualIn;
    preorderOf(root, actualPre); inorderOf(root, actualIn);
    std::cout << name << ": " << (actualPre == pre && actualIn == in ? "PASS" : "FAIL") << '\n';
    destroy(root);
}
int main() {
    check("empty", {}, {});
    check("single", {1}, {1});
    check("branches", {3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
    check("left chain", {3, 2, 1}, {1, 2, 3});
    check("right chain", {1, 2, 3}, {1, 2, 3});
}
