#include <cassert>

// 第 6 题：相同的树（LeetCode 100，Easy，复测）。
// 判断两棵二叉树的结构和对应节点的值是否完全相同。
// 两棵空树视为相同；节点地址不同也可以相同。
//
//     1       1        1       1
//    / \     / \      /         \ 
//   2   3   2   3    2           2
//   第一组相同；第二组结构不同，不相同。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr && q== nullptr){
        return true;
    }
    if(p == nullptr || q == nullptr){
        return false;
    }
    if(p->val != q->val){
        return false;
    }
    bool left = isSameTree(p->left,q->left);
    bool right = isSameTree(p->right,q->right);
    return left&&right;
}

int main() {
    assert(isSameTree(nullptr, nullptr));
    TreeNode a(1), b(2), c(3), d(1), e(2), f(3);
    a.left=&b; a.right=&c; d.left=&e; d.right=&f;
    assert(isSameTree(&a, &d));
    assert(!isSameTree(&a, nullptr));
    f.val=4;
    assert(!isSameTree(&a, &d));
    f.val=3; d.left=nullptr;
    assert(!isSameTree(&a, &d));
}
