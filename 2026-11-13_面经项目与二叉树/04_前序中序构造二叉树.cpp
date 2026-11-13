#include <cassert>
#include <vector>

// 第 4 题：从前序与中序遍历序列构造二叉树（LeetCode 105，Medium，复测）。
// 已知 preorder 和 inorder 描述同一棵树，节点值互不相同，构造并返回根节点。
// 空数组表示空树。前序：根、左、右；中序：左、根、右。
//
//          3
//         / \
//        9  20
//          /  \
//         15   7
// preorder = {3,9,20,15,7}，inorder = {9,3,15,20,7}。
// 返回上图的树。
// 提示：前序首元素是根；根在中序中的位置决定左子树节点数量。
struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    int n = preorder.size();
    if(n == 0 ){
        return nullptr;
    }
    int pos = preorder[0];
    TreeNode* result = new TreeNode(pos);
    int root = 0;
    for(int i = 0; i<n;i++){
        if(pos == inorder[i]){
            root = i;
        }
    }

    std::vector<int> preleft;
    std::vector<int> preright;
    std::vector<int> inleft;
    std::vector<int> inright;
    for(int i=1;i<n;i++){
        if(i <= root){
            preleft.push_back(preorder[i]);
        }
        else{
            preright.push_back(preorder[i]);
        }
    }
    for(int i =0;i<n;i++){
        if( i < root){
            inleft.push_back(inorder[i]);
        }
        if(i>root){
            inright.push_back(inorder[i]);
        }
    }
    result->left = buildTree(preleft,inleft);
    result->right = buildTree(preright,inright);
  
    return result;
}

void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left); destroy(root->right); delete root;
}
int main() {
    assert(buildTree({}, {}) == nullptr);
    TreeNode* root = buildTree({3,9,20,15,7}, {9,3,15,20,7});
    assert(root && root->val == 3 && root->left && root->left->val == 9);
    assert(root->right && root->right->val == 20);
    assert(root->right->left && root->right->left->val == 15);
    assert(root->right->right && root->right->right->val == 7);
    destroy(root);
    TreeNode* one = buildTree({-1}, {-1});
    assert(one && one->val == -1 && !one->left && !one->right);
    destroy(one);
}
