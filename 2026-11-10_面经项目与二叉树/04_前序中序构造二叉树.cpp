#include <cassert>
#include <vector>

// 第 3 题：从前序与中序遍历构造二叉树（LeetCode 105，Medium）
// 节点值互不相同，两个数组描述同一棵树；空数组返回 nullptr。
// preorder = {3, 9, 20, 15, 7}
// inorder  = {9, 3, 15, 20, 7}
//
//        3
//      /   \  
//     9     20
//          /  \  
//         15   7
// 前序第一个值是当前树的根；在中序中找到根，就能划分左右子树。
// 可以采用数组切分的版本，先保证逻辑正确。

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};
// 3 9 20 15 7 pre
// 9 3 15 20 7 in
TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    if(preorder.empty()){
        return nullptr;
    }
    int n = preorder.size();
    int pos = preorder[0];
    TreeNode* result = new TreeNode(pos);
    int index = 0;
    for(int i =0;i < n;i++){
        if(pos == inorder[i]){
            index = i;
            break;
        }
    }

    std::vector<int> preleft;
    std::vector<int> preright;
    std::vector<int> inleft;
    std::vector<int> inright;

    for(int i = 1; i<n;i++){
        if(i <=index){
            preleft.push_back(preorder[i]);
        }else{
            preright.push_back(preorder[i]);
        }
    }
    for(int i =0;i<n;i++){
        if(i < index){
            inleft.push_back(inorder[i]);
        }else if(i>index){
            inright.push_back(inorder[i]);
        }else{
            continue;
        }
    }
    result->left = buildTree(preleft,inleft);
    result->right=buildTree(preright,inright);
    return result;
}

void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left); destroy(root->right); delete root;
}

int main() {
    assert(buildTree({}, {}) == nullptr);
    TreeNode* root = buildTree({3,9,20,15,7}, {9,3,15,20,7});
    assert(root && root->val == 3);
    assert(root->left && root->left->val == 9);
    assert(root->right && root->right->val == 20);
    assert(root->right->left && root->right->left->val == 15);
    assert(root->right->right && root->right->right->val == 7);
    destroy(root);
    TreeNode* single = buildTree({8}, {8});
    assert(single && single->val == 8 && !single->left && !single->right);
    destroy(single);
}
