// 2026-11-07 | LeetCode 236 | 中等 | 递归讲解后复测 | 状态：未开始
// 题意：给定普通二叉树的根，以及树中两个不同节点 p、q，返回最近公共祖先。
// 输入：root、p、q 是节点指针；值互异，p、q 保证存在。输出：祖先节点的地址。
// 边界：节点也可以是自己的祖先；答案可能是根，也可能在同一个子树内。
// 先解释递归：一次调用只处理自己的子树；子调用结束后，控制权回到调用处。
// 局部变量属于各自的调用。不要把“进入递归”和“得到返回值”当作同一时刻。
// 开始前口述：这道题的一次调用承诺返回什么？什么情况下无需继续向下？
// 请先画小树的调用/返回过程，再闭卷补 TODO；有疑问时先要一级提示。
// 只替换 TODO；骨架编译通过不代表掌握，未实现时应有测试失败。
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr){
        return nullptr;
    }
    if(root == p || root ==q){
        return root;
    }
    TreeNode* left = lowestCommonAncestor(root->left,p,q);
    TreeNode* right = lowestCommonAncestor(root->right,p,q);
    if(left != nullptr && right != nullptr){
        return root;
    }
    if(left != nullptr){
        return left;
    }
    return right;


}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* actual, TreeNode* expected) {
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    TreeNode a(3), b(5), c(1), d(6), e(2), f(0), g(8), h(7), i(4);
    a.left = &b; a.right = &c; b.left = &d; b.right = &e;
    c.left = &f; c.right = &g; e.left = &h; e.right = &i;
    check("across root branches", lowestCommonAncestor(&a, &b, &c), &a);
    check("target is ancestor", lowestCommonAncestor(&a, &b, &i), &b);
    check("inside deep subtree", lowestCommonAncestor(&a, &h, &i), &e);
    check("different depths", lowestCommonAncestor(&a, &d, &i), &b);
    check("root is a target", lowestCommonAncestor(&a, &g, &a), &a);
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
