// 2026-11-07 | LeetCode 105 | 中等 | 接续昨日未完成 | 状态：未开始
// 题意：根据同一棵二叉树的前序、中序遍历，重建并返回根节点。
// 输入：两个等长非空数组，值互不相同，保证对应一棵合法树。
// 本地扩展防御约定：两个空数组返回 nullptr（超出原题非空约束）。
// 输出：新树根指针；每个节点用 new 分配，测试负责释放，不返回局部变量地址。
// 边界：空树、单节点、只有左孩子、只有右孩子、左右子树规模不同。
// 昨日写到了辅助函数草稿。今天先说清每段下标的含义，再补实现。
// C++ 不允许在函数体内直接定义普通函数；可在外面定义，或使用 lambda。
// 只替换 TODO；编译通过不代表实现完成，未实现时应有测试失败。
#include <iostream>
#include <unordered_set>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};   //  0 1 2  3  4 
// front 3 9 20 15 7
// mid   9 3 15 20 7
//         pos
TreeNode* buildTree(const std::vector<int>& preorder, const std::vector<int>& inorder) {
    if(preorder.empty()){
        return nullptr;
    }
    int rootValue = preorder[0];
    TreeNode* root = new TreeNode(rootValue);
    int pos = 0;
    while(inorder[pos] != rootValue){
        ++pos;
    }
    std::vector<int> leftPre;//左前
    std::vector<int> rightPre;//右前
    std::vector<int> leftin;//left mid 
    std::vector<int> rightin;// left mid

    for(int i =1; i<preorder.size();i++){        if(i <= pos){
            leftPre.push_back(preorder[i]);
        }else{
            rightPre.push_back(preorder[i]);
        }
    }
    for(int i =0;i<inorder.size(); i++){
        if(i <pos){
            leftin.push_back(inorder[i]);
        }else if(i>pos){
            rightin.push_back(inorder[i]);
        }
    }
    root->left = buildTree(leftPre,leftin);
    root->right = buildTree(rightPre,rightin);
    return root;

}

// 以下仅为测试与清理代码。地址集合可发现重复引用/环，避免测试无限递归。
bool inspect(TreeNode* root, std::vector<int>& pre, std::vector<int>& in,
             std::unordered_set<TreeNode*>& visited) {
    if (!root) return true;
    if (!visited.insert(root).second) return false;
    pre.push_back(root->val);
    bool leftOk = inspect(root->left, pre, in, visited);
    in.push_back(root->val);
    bool rightOk = inspect(root->right, pre, in, visited);
    return leftOk && rightOk;
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, const std::vector<int>& pre,
                     const std::vector<int>& in) {
        TreeNode* root = buildTree(pre, in);
        std::vector<int> actualPre, actualIn;
        std::unordered_set<TreeNode*> visited;
        bool treeShape = inspect(root, actualPre, actualIn, visited);
        bool ok = treeShape && actualPre == pre && actualIn == in;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
        for (TreeNode* node : visited) delete node;
    };
    check("empty", {}, {});
    check("single", {-1}, {-1});
    check("two branches", {3, 9, 20, 15, 7}, {9, 3, 15, 20, 7});
    check("left chain", {3, 2, 1}, {1, 2, 3});
    check("right chain", {1, 2, 3}, {1, 2, 3});
    check("uneven mixed tree", {8, 3, 6, 4, 10, 14}, {3, 4, 6, 8, 10, 14});
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
