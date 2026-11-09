#include <iostream>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 543（Easy，复测）：返回二叉树任意两个节点之间最长路径的边数。
// 路径不一定经过根节点；空树和单节点树的直径均为 0。
//        1
//      /   \
//     2     3
//    / \
//   4   5
// 示例路径 4 -> 2 -> 1 -> 3，共 3 条边，返回 3。
// 可自行添加辅助函数。
int maxdepth(TreeNode*root,int& best){
    if(root == nullptr){
        return 0;
    }
    int leftdepth = maxdepth(root->left,best);
    int rightdepth = maxdepth(root->right,best);
    best = std::max(best,leftdepth+rightdepth);
    return std::max(leftdepth,rightdepth)+1;

}
int diameterOfBinaryTree(TreeNode* root) {
    int best = 0;
    maxdepth(root,best);
    return best;
}

int main() {
    TreeNode n4(4), n5(5), n2(2, &n4, &n5), n3(3), n1(1, &n2, &n3);
    TreeNode c4(4), c3(3, &c4), c2(2, &c3), c1(1, &c2);
    TreeNode a(1), b(2), l(3, &a), r(4, nullptr, &b), center(5, &l, &r), top(6, &center);
    int failed = 0;
    auto check = [&](const char* name, TreeNode* root, int expected) {
        int actual = diameterOfBinaryTree(root);
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << " actual=" << actual << '\n';
        if (!ok) ++failed;
    };
    check("empty", nullptr, 0);
    check("single", &n4, 0);
    check("example", &n1, 3);
    check("chain", &c1, 3);
    check("diameter below root", &top, 4);
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
