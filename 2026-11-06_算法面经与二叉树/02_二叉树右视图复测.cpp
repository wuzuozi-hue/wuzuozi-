#include <iostream>
#include <queue>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

// 从右侧观察二叉树，返回每层可见的节点值；空树返回空数组。
std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> result;
    if(root == nullptr){
        return result;
    }
    std::queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int count = q.size();
        for(int i =0; i<count;i++){
            TreeNode* cur = q.front();
            q.pop();
            if(cur->left != nullptr){
                q.push(cur->left);
            }
            if(cur->right !=nullptr){
                q.push(cur->right);
            }
            if(i == count -1){
                result.push_back(cur->val);
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
    check("left visible", &b, {2, 4});
}
