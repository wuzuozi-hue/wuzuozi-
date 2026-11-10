#include <cassert>
#include <vector>

// 第 10 题：路径总和 II（LeetCode 113，Medium，新题）。
// 找出所有从根到叶子、节点值之和等于 targetSum 的路径。
// 返回每条路径的节点值，路径顺序不限；空树返回空数组。
//
//        5
//       / \ 
//      4   8
//     /   / \ 
//    11  13  4
//   / \     / \ 
//  7   2   5   1
// targetSum=22 -> {{5,4,11,2}, {5,8,4,5}}。
// 与上一题相比：不只判断有没有，要收集所有符合要求的路径。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
void resverse(TreeNode* root,int targetsum,int cnt,std::vector<int>& path,
            std::vector<std::vector<int>>& result){
    if(root == nullptr){
        return ;
    }
    cnt += root->val;
    path.push_back(root->val);
    if(root->left == nullptr && root->right == nullptr && cnt == targetsum){
        result.push_back(path);
    }
    resverse(root->left,targetsum,cnt,path,result);
    resverse(root->right,targetsum,cnt,path,result);
    path.pop_back();
}
std::vector<std::vector<int>> pathSum(TreeNode* root, int targetSum) {
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    resverse(root,targetSum,0,path,result);
    return result;
}

int main() {
    assert(pathSum(nullptr, 0).empty());
    TreeNode a(5), b(4), c(8), d(11), e(13), f(4), g(7), h(2), i(5), j(1);
    a.left=&b; a.right=&c; b.left=&d; c.left=&e; c.right=&f;
    d.left=&g; d.right=&h; f.left=&i; f.right=&j;
    auto paths=pathSum(&a,22);
    assert(paths.size()==2);
    assert((paths[0]==std::vector<int>{5,4,11,2} && paths[1]==std::vector<int>{5,8,4,5}) ||
           (paths[1]==std::vector<int>{5,4,11,2} && paths[0]==std::vector<int>{5,8,4,5}));
    assert(pathSum(&a,9).empty());
    TreeNode negative(-3);
    assert((pathSum(&negative,-3)==std::vector<std::vector<int>>{{-3}}));
}
