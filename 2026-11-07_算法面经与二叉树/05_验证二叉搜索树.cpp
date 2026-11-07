// 2026-11-07 | LeetCode 98 | 中等 | 复测 | 状态：未开始
// 题意：判断树是否为严格二叉搜索树：每个节点的左子树所有值更小，右子树所有值更大。
// 输入：非空树的根指针，节点值可覆盖 int 范围。输出：是否合法；重复值不合法。
// 本地扩展防御约定：空树返回 true（超出原题非空约束）。
// 边界：仅比较直接父子不够；要考虑祖先限制和 INT_MIN/INT_MAX。
// 只替换 TODO；编译通过不代表掌握，未实现时应有测试失败。
#include <climits>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
bool midreverse(TreeNode* root, TreeNode*&previous){
    if(root == nullptr){
        return true;
    }
    if(!midreverse(root->left,previous)){
        return false;
    }
    if(previous !=nullptr && root->val <=previous->val){
        return false;
    }
    previous = root;
    return midreverse(root->right,previous);
}
bool isValidBST(TreeNode* root) {
    TreeNode* previous = nullptr;
    return midreverse(root,previous);
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* root, bool expected) {
        bool ok = isValidBST(root) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    check("empty", nullptr, true);
    TreeNode single(INT_MIN);
    check("single int minimum", &single, true);
    TreeNode a(0), b(INT_MIN), c(INT_MAX);
    a.left = &b; a.right = &c;
    check("valid with int bounds", &a, true);
    TreeNode d(2), e(2);
    d.left = &e;
    check("duplicate", &d, false);
    TreeNode f(5), g(1), h(7), i(4), j(8);
    f.left = &g; f.right = &h; h.left = &i; h.right = &j;
    check("violates ancestor bound", &f, false);
    TreeNode k(2), l(3), m(1);
    k.left = &l; k.right = &m;
    check("invalid direct children", &k, false);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
