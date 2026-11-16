#include <cassert>

// 第 6 题：二叉搜索树中的搜索（LeetCode 700，Easy）。
// 给定二叉搜索树的根节点 root 和目标值 val，返回值为 val 的节点指针；
// 若不存在，返回 nullptr。返回原树中的节点，不创建新节点。
//
//         4
//        / \
//       2   7
//      / \
//     1   3
// val = 2：返回指向节点 2 的指针（它仍连接着节点 1 和 3）。
// val = 5：返回 nullptr。空树也返回 nullptr。
// 二叉搜索树左子树值小于根，右子树值大于根；节点值互不相同。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* searchBST(TreeNode* root, int val) {
    if(root == nullptr){
        return nullptr;
    }
    if(root->val == val){
        return root;
    }
    if(val < root->val){
        return searchBST(root->left,val);
    }else{
        return searchBST(root->right,val);
    }
    return nullptr;
}

int main() {
    TreeNode a(4), b(2), c(7), d(1), e(3);
    a.left=&b; a.right=&c; b.left=&d; b.right=&e;
    assert(searchBST(nullptr, 4) == nullptr);
    assert(searchBST(&a, 4) == &a);
    assert(searchBST(&a, 2) == &b);
    assert(searchBST(&a, 3) == &e);
    assert(searchBST(&a, 7) == &c);
    assert(searchBST(&a, 5) == nullptr);
    assert(searchBST(&a, -1) == nullptr);
}
