// 2026-11-07 | LeetCode 112 | 简单 | 新题 | 状态：未开始
// 题意：判断是否存在从根到叶子的路径，使路径上所有节点值之和等于 targetSum。
// 输入：根指针和目标和；采用原题范围（节点数 <= 5000，节点值和目标和在 [-1000,1000]）。
// 输出：bool；空树返回 false。叶子指左右孩子都为空的节点。
// 边界：必须走到叶子，不能在内部节点提前结束；负数节点不能按“已超过目标”直接剪枝。
// 先举一个“经过内部节点时已达到目标，但没有合格根叶路径”的反例。
// 只替换 TODO；编译通过不代表掌握，未实现时应有测试失败。
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

bool hasPathSum(TreeNode* root, int targetSum) {
    if(root == nullptr){
        return false;
    }
    if(root->left == nullptr && root->right == nullptr){
        return root->val == targetSum;
    }
    int remaining = targetSum - root->val;
    return hasPathSum(root->left,remaining)|| hasPathSum(root->right,remaining);
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* root, int target, bool expected) {
        bool ok = hasPathSum(root, target) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    check("empty target zero", nullptr, 0, false);
    TreeNode single(7);
    check("single matching leaf", &single, 7, true);
    TreeNode a(5), b(4), c(8), d(11), e(13), f(4), g(7), h(2), i(1);
    a.left = &b; a.right = &c; b.left = &d; c.left = &e; c.right = &f;
    d.left = &g; d.right = &h; f.right = &i;
    check("existing root to leaf path", &a, 22, true);
    check("no matching path", &a, 100, false);
    TreeNode j(1), k(2);
    j.left = &k;
    check("internal node does not count", &j, 1, false);
    TreeNode l(5), m(-7), n(2);
    l.right = &m; m.left = &n;
    check("negative values and zero sum", &l, 0, true);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
