#include <cassert>
#include <vector>

// 第 2 题：路径总和 II（LeetCode 113，Medium，复测）
// 找出所有从根到叶子的路径，使路径上所有节点值的和等于 targetSum。
// 叶子节点的左右孩子均为空；空树返回空数组，节点值可以为负数。
//
//         5
//        / \
//       4   8
//      /   / \
//     11  13  4
//    /  \    / \
//   7    2  5   1
// targetSum = 22：{{5, 4, 11, 2}, {5, 8, 4, 5}}，顺序不限。
// targetSum = 9：结果为空，因为 5 -> 4 没有到叶子节点。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
std::vector<std::vector<int>> sum(TreeNode*root,int targetsum,int cnt,
    std::vector<std::vector<int>>&result,std::vector<int> path){
        if(root == nullptr){
            return result;
        }
        cnt += root->val;
        path.push_back(root->val);
        if(root->left == nullptr && root->right == nullptr && cnt == targetsum){
            result.push_back(path);
        }
        sum(root->left,targetsum,cnt,result,path);
        sum(root->right,targetsum,cnt,result,path);
        return result;
    }
// 可以自行添加辅助函数。
std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum) {
    std::vector<int> path;
    std::vector<std::vector<int>> result;
    int cnt = 0;
    return sum(root, targetSum,cnt,result,path);
}

int main() {
    assert(pathSum(nullptr, 0).empty());
    TreeNode a(5), b(4), c(8), d(11), e(13), f(4), g(7), h(2), i(5), j(1);
    a.left = &b; a.right = &c; b.left = &d; c.left = &e; c.right = &f;
    d.left = &g; d.right = &h; f.left = &i; f.right = &j;
    auto paths = pathSum(&a, 22);
    assert(paths.size() == 2);
    assert((paths[0] == std::vector<int>{5,4,11,2} && paths[1] == std::vector<int>{5,8,4,5}) ||
           (paths[1] == std::vector<int>{5,4,11,2} && paths[0] == std::vector<int>{5,8,4,5}));
    assert(pathSum(&a, 9).empty());
    TreeNode negative(-3);
    assert((pathSum(&negative, -3) == std::vector<std::vector<int>>{{-3}}));
}
