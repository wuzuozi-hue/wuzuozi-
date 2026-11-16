#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

// 第 9 题：二叉树的所有路径（LeetCode 257，Easy）。
// 返回所有从根节点到叶子节点的路径，以字符串表示，节点间使用 "->"。
// 叶子节点左右孩子均为空；结果顺序不限，空树返回空数组。
//
//      1
//     / \
//    2   3
//     \
//      5
// 返回 {"1->2->5", "1->3"}。
// 示例二：单节点 -1，返回 {"-1"}。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
std::vector<std::string> sum(TreeNode*root,std::vector<std::string>&result,
    std::string path){
        if(root == nullptr){
            return result;
        }
        if(!path.empty()){
            path +="->";
        }
        path +=std::to_string(root->val);
        if(root->left == nullptr && root->right == nullptr){
            result.push_back(path);
        }
        sum(root->left,result,path);
        sum(root->right,result,path);
        return result;
    }

// 可以添加辅助函数。
std::vector<std::string> binaryTreePaths(TreeNode* root) {
    std::vector<std::string> result;
    std::string path;
    return sum(root,result,path);
}

int main() {
    assert(binaryTreePaths(nullptr).empty());
    TreeNode a(1), b(2), c(3), d(5);
    a.left=&b; a.right=&c; b.right=&d;
    auto paths = binaryTreePaths(&a);
    std::sort(paths.begin(), paths.end());
    assert((paths == std::vector<std::string>{"1->2->5", "1->3"}));
    TreeNode one(-1);
    assert((binaryTreePaths(&one) == std::vector<std::string>{"-1"}));
    TreeNode x(-2), y(0);
    x.left=&y;
    assert((binaryTreePaths(&x) == std::vector<std::string>{"-2->0"}));
}
