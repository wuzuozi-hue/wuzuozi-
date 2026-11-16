#include <algorithm>
#include <cassert>
#include <cstdlib>

// 第 5 题：平衡二叉树（LeetCode 110，Easy，新题）。
// 判断一棵树是否为高度平衡二叉树：对每一个节点，左右子树的高度差
// 的绝对值不超过 1。空树是平衡的。树的高度按节点数量计算。
//
//       1              1
//      / \            /
//     2   3          2
//    /              /
//   4              3
//  返回 true       返回 false：根节点左右子树高度差为 2。
//
// 注意：不是只判断根节点，树中每个节点都要满足条件。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 可以自行添加辅助函数。
int depth(TreeNode* root, int& dif){
    if(root == nullptr){
        return 0;
    }
    int leftdepth = depth(root->left,dif);
    int rightdepth = depth(root->right,dif);
    dif = std::max(dif,std::abs(leftdepth-rightdepth));
    return std::max(leftdepth,rightdepth) +1;
}
bool isBalanced(TreeNode* root) {
    if(root == nullptr){
        return true;
    }
    int dif = 0;
    depth(root,dif);
    if(dif >1){
        return false;
    }
    return true;
}

int main() {
    assert(isBalanced(nullptr));
    TreeNode a(1), b(2), c(3), d(4);
    assert(isBalanced(&a));
    a.left=&b; a.right=&c; b.left=&d;
    assert(isBalanced(&a));
    a.right=nullptr; b.left=&c; c.left=nullptr;
    assert(!isBalanced(&a));
    // 根节点高度差为 1，但左子树内部不平衡。
    TreeNode e(5), f(6), g(7), h(8), i(9), j(10);
    e.left=&f; e.right=&g; f.left=&h; h.left=&i; g.left=&j;
    assert(!isBalanced(&e));
}
