// 2026-11-07 | LeetCode 101 | 简单 | 新题 | 状态：未开始
// 题意：判断二叉树是否关于根节点的中轴线镜像对称，既比较结构也比较值。
// 输入：非空树的根指针。输出：bool；单节点为 true。
// 本地扩展防御约定：空树返回 true（超出原题非空约束）。
// 边界：值相同但空位置不同仍不对称；一边缺失不对称；不能只检查各层值集合。
// 先自己画两个互为镜像的小树，再说明一次判断需要哪些输入。
// 只替换 TODO；编译通过不代表掌握，未实现时应有测试失败。
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
bool mirror(TreeNode*left,TreeNode*right){
    if(left == nullptr &&right == nullptr){
        return true;
    }
    if(left == nullptr || right == nullptr){
        return false;
    }
    if(left ->val !=right->val){
        return false;
    }
    bool outer = mirror(left->left,right->right);
    bool inner = mirror(left->right,right->left);
    return outer &&inner;
}
bool isSymmetric(TreeNode* root) {
   if(root ==nullptr){
    return true;
   }
   return mirror(root->left,root->right);
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* root, bool expected) {
        bool ok = isSymmetric(root) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    check("empty", nullptr, true);
    TreeNode single(1);
    check("single", &single, true);
    TreeNode a(1), b(2), c(2), d(3), e(4), f(4), g(3);
    a.left = &b; a.right = &c; b.left = &d; b.right = &e; c.left = &f; c.right = &g;
    check("full mirror", &a, true);
    TreeNode h(1), i(2), j(2), k(3), l(3);
    h.left = &i; h.right = &j; i.right = &k; j.right = &l;
    check("same values wrong positions", &h, false);
    TreeNode m(1), n(2), o(2), p(3), q(4);
    m.left = &n; m.right = &o; n.left = &p; o.right = &q;
    check("mirror shape different values", &m, false);
    TreeNode r(1), s(2);
    r.left = &s;
    check("one side missing", &r, false);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
