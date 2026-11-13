#include <cassert>

// 第 1 题：路径总和（LeetCode 112，Easy，复测）。
// 判断是否有从根到叶子节点的路径，节点值之和等于 targetSum。
// 叶子节点：左右孩子均为空。
// 空树返回 false；节点值和目标值可以是负数。
// 示例：
//         5
//        / \
//       4   8
//      /   / \
//     11  13  4
//    /  \      \
//   7    2      1
// 输入：targetSum = 22
// 输出：true；路径 5 -> 4 -> 11 -> 2，和为 22。
// targetSum = 9 时返回 false：5 -> 4 的和虽然为 9，4 却不是叶子。
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

bool hasPathSum(TreeNode* root, int targetSum) {
    if(root == nullptr){
        return false;
    }
    targetSum -= root->val;
    if(root->left  == nullptr && root->right == nullptr && targetSum == 0){
        return true;
    }
    return hasPathSum(root->left,targetSum)  ||
    hasPathSum(root->right,targetSum);

}

int main() {
    assert(!hasPathSum(nullptr, 0));
    TreeNode a(5), b(4), c(8), d(11), e(13), f(4), g(7), h(2), i(1);
    a.left = &b; a.right = &c; b.left = &d; c.left = &e; c.right = &f;
    d.left = &g; d.right = &h; f.right = &i;
    assert(hasPathSum(&a, 22));
    assert(!hasPathSum(&a, 9));
    assert(hasPathSum(&i, 1));
    TreeNode negative(-3);
    assert(hasPathSum(&negative, -3));
    assert(!hasPathSum(&negative, 0));
}
