#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 617（Easy，新题）：合并两棵二叉树。
// 对应位置两个节点都有：值相加；只有一个节点：保留它的值和后代。
// 本练习要求新建结果树，不修改输入，也不复用输入节点。
// 输入：     1           2           结果：     3
//           / \         / \                   / \
//          3   2       1   3                 4   5
//         /             \   \               / \   \
//        5               4   7             5   4   7
// 两棵都是空树，返回 nullptr。
// 可以先处理空节点，再计算当前节点的值，递归合并左右子树。
TreeNode* mergeTrees(TreeNode* a, TreeNode* b) {
    if(a == nullptr && b == nullptr){
        return nullptr;
    }
    int valueA = (a== nullptr)? 0:a->val;
    int valueB = (b== nullptr)? 0:b->val;

    TreeNode* result = new TreeNode(valueA + valueB);
    
    result->left = mergeTrees(
        a == nullptr? nullptr: a->left,
        b == nullptr? nullptr: b->left
    );
     result->right = mergeTrees(
        a == nullptr? nullptr: a->right,
        b == nullptr? nullptr: b->right
    );
    return result;
}

bool equals(TreeNode* a, TreeNode* b) {
    if (!a || !b) return a == b;
    return a->val == b->val && equals(a->left,b->left) && equals(a->right,b->right);
}
void destroy(TreeNode* root) {
    if (!root) return;
    destroy(root->left); destroy(root->right); delete root;
}
int main() {
    TreeNode a5(5),a3(3,&a5),a2(2),a1(1,&a3,&a2);
    TreeNode b4(4),b1(1,nullptr,&b4),b7(7),b3(3,nullptr,&b7),b2(2,&b1,&b3);
    TreeNode e5(5),e4(4),eleft(4,&e5,&e4),e7(7),eright(5,nullptr,&e7),expected(3,&eleft,&eright);
    int failed=0;
    auto check=[&](const char* name,TreeNode* x,TreeNode* y,TreeNode* expectedTree){
        TreeNode* result=mergeTrees(x,y);
        bool ok=equals(result,expectedTree);
        std::cout<<name<<": "<<(ok?"PASS":"FAIL")<<'\n';
        if(!ok) ++failed;
        // 用户结果可能复用栈节点，因此这里不自动 delete，避免错误实现导致崩溃。
    };
    check("both empty",nullptr,nullptr,nullptr);
    check("example",&a1,&b2,&expected);
    check("one empty",nullptr,&a1,&a1);
    check("other empty",&b2,nullptr,&b2);
    std::cout<<"Failed cases: "<<failed<<'\n';
    return failed==0?0:1;
}
