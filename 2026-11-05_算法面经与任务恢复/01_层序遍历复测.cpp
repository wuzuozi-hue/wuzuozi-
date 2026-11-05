#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 返回每一层的节点值，层内从左到右。
std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector<std::vector<int>> result;
    if(root == nullptr){
        return result;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int count = q.size();
        std::vector<int> level;
        for(int i = 0 ;i<count; i++){
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
             if(node->left != nullptr){
                q.push(node->left);
             }
             if(node->right != nullptr){
                q.push(node->right);
             }
        }
       result.push_back(level);
    }
    return result;
}

void check(const char* name, TreeNode* root, const std::vector<std::vector<int>>& expected) {
    std::cout << name << ": " << (levelOrder(root) == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    TreeNode a(1), b(2), c(3), d(4), e(5);
    check("single", &a, {{1}});
    a.left = &b; a.right = &c; b.right = &d; c.left = &e;
    check("branching", &a, {{1}, {2, 3}, {4, 5}});
    check("one side", &b, {{2}, {4}});
}
