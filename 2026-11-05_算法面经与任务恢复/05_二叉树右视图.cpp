#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 从右侧看，每一层只能看到最右边的节点。
std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> result;
    if(root == nullptr){
        return result;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int count = q.size();
        for(int i = 0; i<count; i++){
            TreeNode* node =q.front();
            q.pop();
            if(node->left != nullptr){
                q.push(node->left);
             }
            if(node->right != nullptr){
                q.push(node->right);
            }
            if(i == count - 1){
                result.push_back(node->val);
            }
        }
    }
    return result;
}

void check(const char* name, TreeNode* root, const std::vector<int>& expected) {
    std::cout << name << ": " << (rightSideView(root) == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    TreeNode a(1), b(2), c(3), d(4), e(5);
    check("single", &a, {1});
    a.left = &b; a.right = &c; b.right = &d; c.left = &e;
    check("branches", &a, {1, 3, 5});
    check("left only", &c, {3, 5});
}
