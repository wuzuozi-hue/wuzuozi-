#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 98（Mid，复测）
// 验证给定二叉树是否为二叉搜索树：对每个节点，左子树所有值严格小于它，
// 右子树所有值严格大于它，左右子树自身也要满足这一规则。空树有效。
// 有效：       2              无效：      5
//             / \                        / \
//            1   3                      1   6
//                                          / \
//                                         3   7
// 右侧的 3 虽然小于父节点 6，但它位于 5 的右子树，违反了规则。
// 你可以使用辅助函数，自己选择实现方式。
bool midreverse(TreeNode* root,TreeNode*& previous){
    if(root == nullptr){
        return true;
    }
    if(!midreverse(root->left,previous)){
        return false;
    }
    if(previous != nullptr && root->val <= previous->val){
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
    int failed = 0;
    auto check = [&](const char* name, TreeNode* root, bool expected) {
        bool actual = isValidBST(root);
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) ++failed;
    };
    TreeNode a1(1), a3(3), a2(2, &a1, &a3);
    TreeNode b1(1), b3(3), b7(7), b6(6, &b3, &b7), b5(5, &b1, &b6);
    TreeNode duplicate(2), dupRoot(2, &duplicate, nullptr);
    TreeNode low(-2147483647 - 1), high(2147483647), boundary(0, &low, &high);
    check("empty", nullptr, true);
    check("valid", &a2, true);
    check("global constraint", &b5, false);
    check("duplicate", &dupRoot, false);
    check("int boundaries", &boundary, true);
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
