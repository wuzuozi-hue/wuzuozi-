#include <cassert>
#include <vector>

// 第 2 题：从前序与中序遍历序列构造二叉树（LeetCode 105，Medium）。
// 已知 preorder 是前序遍历，inorder 是中序遍历，返回构造好的根节点。
// 题目保证节点值互不相同，两个序列有效且属于同一棵树。
//
//        3
//       / \
//      9  20
//         / \
//        15  7
// preorder = {3, 9, 20, 15, 7}（根、左、右）
// inorder  = {9, 3, 15, 20, 7}（左、根、右）
//
// 提示：前序第一个值是当前树的根；在中序中找到它后，
// 左边是左子树，右边是右子树。左子树长度可用于切分前序。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    if(preorder.size() == 0){
        return nullptr;
    }
    int n = preorder.size();
    int pos = preorder[0];
    int index = 0;
    for(int i =0;i<n;i++){
        if(pos == inorder[i]){
            index = i;
        }
    }
    TreeNode* result = new TreeNode(pos);
    std::vector<int> preleft;
    std::vector<int> preright;
    std::vector<int> inleft;
    std::vector<int> inright;

    for(int i = 1;i<n;i++){
        if(i <= index){
            preleft.push_back(preorder[i]);
        }else{
            preright.push_back(preorder[i]);
        }
    }
    for(int i =0;i<n;i++){
        if(i < index){
            inleft.push_back(inorder[i]);
        }
        if(i > index){
            inright.push_back(inorder[i]);
        }
    }
    result->left = buildTree(preleft,inleft);
    result->right = buildTree(preright,inright);
    return result;
}

void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}

int main() {
    assert(buildTree({}, {}) == nullptr);
    TreeNode* root = buildTree({3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
    assert(root && root->val == 3);
    assert(root->left && root->left->val == 9);
    assert(root->right && root->right->val == 20);
    assert(root->right->left && root->right->left->val == 15);
    assert(root->right->right && root->right->right->val == 7);
    assert(!root->left->left && !root->left->right);
    assert(!root->right->left->left && !root->right->left->right);
    destroy(root);
    TreeNode* one = buildTree({9}, {9});
    assert(one && one->val == 9 && !one->left && !one->right);
    destroy(one);
}
