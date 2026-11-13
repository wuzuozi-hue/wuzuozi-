#include <cassert>

// 第 6 题：相同的树（LeetCode 100，Easy，复测）。
// 判断两棵二叉树的结构和对应节点的值是否完全相同。
// 两棵空树相同；一棵为空、另一棵非空则不同。
//
//      1         1             1         1
//     / \       / \           /           \
//    2   3     2   3         2             2
//    返回 true                 返回 false（结构不同）
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p==nullptr && q==nullptr){
        return true;
    }
    if(p == nullptr && q!=nullptr){
        return false;
    }
    if(p != nullptr && q== nullptr){
        return false;
    }
    if(p->val !=q->val){
        return false;
    }
    return isSameTree(p->left,q->left)&&
    isSameTree(p->right,q->right);
    
}

int main() {
    assert(isSameTree(nullptr, nullptr));
    TreeNode a(1), b(2), c(3), x(1), y(2), z(3);
    a.left=&b; a.right=&c; x.left=&y; x.right=&z;
    assert(isSameTree(&a, &x));
    assert(!isSameTree(&a, nullptr));
    z.val=4;
    assert(!isSameTree(&a, &x));
    z.val=3; x.left=nullptr;
    assert(!isSameTree(&a, &x));
}
