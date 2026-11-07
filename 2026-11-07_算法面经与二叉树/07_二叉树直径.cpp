// 2026-11-07 | LeetCode 543 | 简单 | 复测 | 状态：未开始
// 题意：返回树中任意两个节点之间最长路径的边数，该路径不一定经过根。
// 输入：非空树的根指针。输出：非负整数，单节点为 0。
// 本地扩展防御约定：空树返回 0（超出原题非空约束）。
// 边界：区分节点数与边数；同一程序多次调用，结果不能受上一次调用污染。
// 只替换 TODO；编译通过不代表掌握，未实现时应有测试失败。
#include <algorithm>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
int depth(TreeNode* root,int& best){
    if(root ==nullptr){
        return 0;
    }
    int leftdepth = depth(root->left,best);
    int rightdepth = depth(root->right,best);
    best = std::max(best,leftdepth+rightdepth);
    return std::max(leftdepth,rightdepth) +1;
}
int diameterOfBinaryTree(TreeNode* root) {
    int best =0;
    depth(root,best);
    return best;
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* root, int expected) {
        int actual = diameterOfBinaryTree(root);
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL")
                  << " (actual=" << actual << ", expected=" << expected << ")\n";
        failures += !ok;
    };
    check("empty", nullptr, 0);
    TreeNode a(1), b(2), c(3), d(4), e(5);
    a.left = &b; a.right = &c; b.left = &d; b.right = &e;
    check("through root", &a, 3);
    TreeNode f(1), g(2), h(3), i(4);
    f.right = &g; g.right = &h; h.right = &i;
    check("chain uses edges", &f, 3);
    TreeNode j(1), k(2), l(3), m(4), n(5), o(6);
    j.left = &k; k.left = &l; k.right = &m; l.left = &n; m.right = &o;
    check("longest path below root", &j, 4);
    TreeNode single(99);
    check("single after large tree", &single, 0);
    check("repeat earlier tree", &a, 3);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
