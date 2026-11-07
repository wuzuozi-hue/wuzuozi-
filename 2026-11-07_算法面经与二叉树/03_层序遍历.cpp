// 2026-11-07 | LeetCode 102 | 中等 | 复测 | 状态：未开始
// 题意：返回二叉树从上到下的每一层，每层节点值按从左到右排列。
// 输入：根节点指针，可为空。输出：二维数组；空树返回 {}。
// 边界：单节点、稀疏层、单侧链；每一层必须单独组成一个数组。
// 只替换 TODO；编译通过不代表掌握，未实现时应有测试失败。
#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if(root == nullptr){
        return result;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int n = q.size();
        std::vector<int> level;
        for(int i = 0; i<n;i++){
            TreeNode* pre = q.front();
            q.pop();
            level.push_back(pre->val);
            if(pre->left !=nullptr){
                q.push(pre->left);
            }
            if(pre->right !=nullptr){
                q.push(pre->right);
            }
        }
        result.push_back(level);
    }
    return result;
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* root,
                     const std::vector<std::vector<int>>& expected) {
        bool ok = levelOrder(root) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    check("empty", nullptr, {});
    TreeNode single(42);
    check("single", &single, {{42}});
    TreeNode a(3), b(9), c(20), d(15), e(7);
    a.left = &b; a.right = &c; c.left = &d; c.right = &e;
    check("sparse tree", &a, {{3}, {9, 20}, {15, 7}});
    TreeNode f(1), g(2), h(3);
    f.left = &g; g.left = &h;
    check("left chain", &f, {{1}, {2}, {3}});
    TreeNode i(1), j(2), k(3), l(4), m(5);
    i.left = &j; i.right = &k; j.right = &l; k.left = &m;
    check("same level order", &i, {{1}, {2, 3}, {4, 5}});
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
