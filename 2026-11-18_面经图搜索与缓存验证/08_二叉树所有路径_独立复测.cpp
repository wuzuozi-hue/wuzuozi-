#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

// 257. 二叉树的所有路径
// 返回从根节点到每个叶子节点的所有路径，用 "->" 分隔相邻节点的值。
// 返回路径的顺序不限，空树返回空结果。
// 根节点 1 的左右孩子为 2、3，节点 2 的右孩子为 5。
// 预期 {"1->2->5", "1->3"}。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

    explicit TreeNode(int value) : val(value) {}
};
std::vector<std::string> sum(TreeNode*root,std::string path,
    std::vector<std::string>& result){
        if(root == nullptr){
            return result;
        }
        if(!path.empty()){
            path+="->";
        }
        path+=std::to_string(root->val);
        if(root->left == nullptr && root->right == nullptr){
            result.push_back(path);
        }
        sum(root->left,path,result);
        sum(root->right,path,result);
        return result;
    }
std::vector<std::string> binaryTreePaths(TreeNode* root) {
    std::string path;
    std::vector<std::string> result;
    result = sum(root,path,result);
    return result;
}

void check(TreeNode* root, std::vector<std::string> expected) {
    auto actual = binaryTreePaths(root);
    std::sort(actual.begin(), actual.end());
    std::sort(expected.begin(), expected.end());
    assert(actual == expected);
}

int main() {
    TreeNode a(1), b(2), c(3), d(5);
    a.left = &b;
    a.right = &c;
    b.right = &d;
    check(&a, {"1->2->5", "1->3"});

    TreeNode solo(-8);
    check(&solo, {"-8"});
    check(nullptr, {});

    TreeNode e(-10), f(0), g(12), h(-3);
    e.right = &f;
    f.left = &g;
    f.right = &h;
    check(&e, {"-10->0->12", "-10->0->-3"});

    std::cout << "Binary tree paths: all checks passed\n";
}
