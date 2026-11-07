// 2026-11-07 | LeetCode 199 | 中等 | 复测 | 状态：未开始
// 题意：从右侧看二叉树，返回每层最右边的节点值，顺序从上到下。
// 输入：根指针，可为空。输出：一维数组；空树返回 {}。
// 边界：右视图不等于一直沿右孩子走；更深一层可来自左子树。
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

std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> result;
    if(root ==nullptr){
        return result;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int n =q.size();
        for(int i =0;i<n;i++){
            TreeNode* cur  = q.front();
            q.pop();
            if(cur->left !=nullptr){
                q.push(cur->left);
            }
            if(cur->right !=nullptr){
                q.push(cur->right);
            }
            if( i == n -1){
                result.push_back(cur->val);
            }
        }
    }
    return result;
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, TreeNode* root, const std::vector<int>& expected) {
        bool ok = rightSideView(root) == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    check("empty", nullptr, {});
    TreeNode single(-2);
    check("single", &single, {-2});
    TreeNode a(1), b(2), c(3), d(5), e(4);
    a.left = &b; a.right = &c; b.right = &d; c.right = &e;
    check("both sides", &a, {1, 3, 4});
    TreeNode f(1), g(2), h(3), i(4), j(5);
    f.left = &g; f.right = &h; g.right = &i; i.left = &j;
    check("left subtree extends deeper", &f, {1, 3, 4, 5});
    TreeNode k(6), l(7), m(8);
    k.left = &l; l.left = &m;
    check("left only", &k, {6, 7, 8});
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
