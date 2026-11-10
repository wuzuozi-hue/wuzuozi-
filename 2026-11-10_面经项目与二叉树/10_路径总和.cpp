#include <cassert>

// 第 9 题：路径总和（LeetCode 112，Easy，新题）。
// 给定二叉树和 targetSum，判断是否存在一条“根节点到叶子节点”的路径，
// 使路径上所有节点值之和等于 targetSum。空树返回 false。
// 叶子节点是没有左、右孩子的节点；节点值和目标值可以是负数。
//
//          5
//        /   \ 
//       4     8
//      /     / \ 
//     11    13  4
//    /  \         \ 
//   7    2         1
// targetSum=22：5 -> 4 -> 11 -> 2，返回 true。
// targetSum=9：5 -> 4 虽然和是 9，但 4 不是叶子，不能作为答案。

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
    targetSum -= root->val;
    if(root->left==nullptr && root->right==nullptr && targetSum == 0){
        return true;
    }
    return   hasPathSum(root->left,targetSum)||
            hasPathSum(root->right,targetSum);
 

}

int main() {
    assert(!hasPathSum(nullptr, 0));
    TreeNode a(5), b(4), c(8), d(11), e(13), f(4), g(7), h(2), i(1);
    a.left=&b; a.right=&c; b.left=&d; c.left=&e; c.right=&f;
    d.left=&g; d.right=&h; f.right=&i;
    assert(hasPathSum(&a, 22));
    assert(!hasPathSum(&a, 9));
    assert(hasPathSum(&i, 1));
    TreeNode negative(-3);
    assert(hasPathSum(&negative, -3));
    assert(!hasPathSum(&negative, 0));
}
