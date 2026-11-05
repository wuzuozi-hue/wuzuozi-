#include <algorithm>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
int depth(TreeNode* node,int& best){
    if(node == nullptr ){
        return 0;
    }
    int leftdepth = depth(node->left,best);
    int rightdepth = depth(node->right,best);
    best = std::max(best,leftdepth +rightdepth);
    return std::max(leftdepth,rightdepth) + 1;
}
// 直径按路径上的边数计算。空树和单节点的直径均为 0。
int diameterOfBinaryTree(TreeNode* root) {
   int best = 0;
   depth(root,best);
   return best;
}

void check(const char* name, int actual, int expected) {
    std::cout << name << ": " << (actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", diameterOfBinaryTree(nullptr), 0);
    TreeNode a(1), b(2), c(3), d(4), e(5), f(6);
    check("single", diameterOfBinaryTree(&a), 0);
    a.left = &b; a.right = &c; b.left = &d; b.right = &e;
    check("branches", diameterOfBinaryTree(&a), 3);
    d.left = &f;
    check("deeper branch", diameterOfBinaryTree(&a), 4);
}
