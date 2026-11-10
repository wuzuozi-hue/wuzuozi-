#include <cassert>
#include <queue>
#include <vector>

// 第 8 题：二叉树的右视图（LeetCode 199，Medium，复测）。
// 从树的右侧看，每一层能看到的最右边节点依次组成结果。
// 空树返回空数组。
//
//       1              从右侧看到：1
//      / \             从右侧看到：3
//     2   3            从右侧看到：4
//      \   \ 
//       5   4
// 返回 {1, 3, 4}。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> result;
    if(root == nullptr){
        return result;
    }
    std::queue <TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int n = q.size();
        for(int i = 0;i<n;i++){
            TreeNode* cur = q.front();
            q.pop();
            if(cur->left !=nullptr){
                q.push(cur->left);
            }
            if(cur->right !=nullptr){
                q.push(cur->right);
            }
            if( i == n -1){
                result.push_back(cur->val);
            }
        }
    }
    return result;
}

int main() {
    assert(rightSideView(nullptr).empty());
    TreeNode a(1), b(2), c(3), d(5), e(4);
    a.left=&b; a.right=&c; b.right=&d; c.right=&e;
    assert((rightSideView(&a) == std::vector<int>{1,3,4}));
    TreeNode x(8), y(9), z(10);
    x.left=&y; y.left=&z;
    assert((rightSideView(&x) == std::vector<int>{8,9,10}));
    assert((rightSideView(&z) == std::vector<int>{10}));
}
