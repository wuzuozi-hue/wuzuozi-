#include <cassert>
#include <algorithm>
#include <vector>
// 第 7 题：二叉搜索树中第 K 小的元素（LeetCode 230，Medium）。
// 给定二叉搜索树 root 和整数 k，返回树中第 k 小的节点值。
// 题目保证节点值互不相同，树非空，1 <= k <= 树的节点数。
//
//       3
//      / \
//     1   4
//      \
//       2
// 节点从小到大是 1、2、3、4。
// k = 1 返回 1；k = 3 返回 3。
//
// 示例二：只有一个节点 8，k = 1，返回 8。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
std::vector<int> sum(TreeNode* root, std::vector<int>&result){
    if(root == nullptr){
        return result;
    }
    sum(root->left,result);
    result.push_back(root->val);
    sum(root->right,result);
    return result;
}
// 可以添加辅助函数。
int kthSmallest(TreeNode* root, int k) {
    std::vector<int> result;
    result = sum(root,result);
    return result[k-1];
}

int main() {
    TreeNode a(3), b(1), c(4), d(2);
    a.left=&b; a.right=&c; b.right=&d;
    assert(kthSmallest(&a, 1) == 1);
    assert(kthSmallest(&a, 2) == 2);
    assert(kthSmallest(&a, 3) == 3);
    assert(kthSmallest(&a, 4) == 4);
    TreeNode one(8);
    assert(kthSmallest(&one, 1) == 8);
    TreeNode neg(-2), neg2(-3), zero(0);
    neg.left=&neg2; neg.right=&zero;
    assert(kthSmallest(&neg, 1) == -3);
    assert(kthSmallest(&neg, 3) == 0);
}
