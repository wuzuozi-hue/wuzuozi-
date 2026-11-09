#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

// LeetCode 105（中等，复测）：根据前序和中序遍历构造二叉树。
// 条件：节点值互不相同，两个遍历有效且描述同一棵树；空数组代表空树。
// 示例：preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
//        3
//       / \
//      9  20
//        /  \
//       15   7
// 提示词（按之前约定保留）：前序第一个是当前树根；在中序中找到根；
// 中序根左边属于左子树，右边属于右子树；将两种遍历切成对应子树后递归。
// 可以使用辅助函数或切分 vector，完成后返回根节点。
// 已经替你写好「找根、拆分数组」；请补上两次递归和返回值。
TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    if (preorder.empty()) {
        return nullptr;
    }

    int rootValue = preorder[0];
    TreeNode* root = new TreeNode(rootValue);

    // 在中序数组中找到根，左边元素的个数就是左子树节点数。
    int rootIndex = 0;
    while (inorder[rootIndex] != rootValue) {
        ++rootIndex;
    }
    int leftSize = rootIndex;

    // 左闭右开区间：[起点, 终点)，不包含终点。
    std::vector<int> leftPre(preorder.begin() + 1, preorder.begin() + 1 + leftSize);
    std::vector<int> rightPre(preorder.begin() + 1 + leftSize, preorder.end());
    std::vector<int> leftIn(inorder.begin(), inorder.begin() + rootIndex);
    std::vector<int> rightIn(inorder.begin() + rootIndex + 1, inorder.end());

    // TODO 1：递归构造左子树，将结果接到 root->left。
    root->left = buildTree(leftPre,leftIn);
    // TODO 2：递归构造右子树，将结果接到 root->right。
    root->right =buildTree(rightPre,rightIn);
    // TODO 3：返回当前构造好的根节点（替换下面的占位返回值）。
    return root;
}
void preorderWalk(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorderWalk(root->left, out);
    preorderWalk(root->right, out);
}
void inorderWalk(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    inorderWalk(root->left, out);
    out.push_back(root->val);
    inorderWalk(root->right, out);
}
void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}
int main() {
    int failed = 0;
    auto check = [&](const char* name, std::vector<int> pre, std::vector<int> in) {
        TreeNode* root = buildTree(pre, in);
        std::vector<int> actualPre, actualIn;
        preorderWalk(root, actualPre);
        inorderWalk(root, actualIn);
        bool ok = actualPre == pre && actualIn == in;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) ++failed;
        destroy(root);
    };
    check("example", {3,9,20,15,7}, {9,3,15,20,7});
    check("empty", {}, {});
    check("single", {9}, {9});
    check("left chain", {1,2,3}, {3,2,1});
    check("right chain", {1,2,3}, {1,2,3});
    check("uneven tree", {8,4,6,12}, {4,6,8,12});
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}

