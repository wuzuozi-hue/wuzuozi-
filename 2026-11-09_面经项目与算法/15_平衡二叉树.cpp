#include <iostream>
#include <algorithm>
#include <cstdlib>
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 110（Easy，新题）：判断一棵二叉树是否为高度平衡二叉树。
// 对每个节点，其左、右子树的高度差的绝对值都不超过 1。
// 空树高度为 0，单个节点的树高度为 1；空树是平衡树。
// 平衡：       1               不平衡：      1
//             / \                            /
//            2   3                          2
//                                          /
//                                         3
// 要检查所有节点：只检查根节点的左右高度差还不够。
// 可以使用辅助函数计算高度，或选择你熟悉的方法。
int cntdepth(TreeNode*root,int& dif){
    if(root == nullptr){
        return 0;
    }
    int leftdepth = cntdepth(root->left,dif);
    int rightdepth =cntdepth(root->right,dif);
    dif = std::max(dif,std::abs(leftdepth - rightdepth));
    return std::max(leftdepth,rightdepth) +1;
}
bool isBalanced(TreeNode* root) {
    int dif = 0;
    cntdepth(root,dif);
    if(dif ==0 || dif == 1){
        return true;
    }
    return false;
}

int main() {
    TreeNode a2(2),a3(3),a1(1,&a2,&a3);
    TreeNode b3(3),b2(2,&b3),b1(1,&b2);
    TreeNode l3(3),l2(2,&l3),l1(1,&l2);
    TreeNode r3(3),r2(2,&r3),r1(1,nullptr,&r2);
    TreeNode deep(0,&l1,&r1);
    int failed=0;
    auto check=[&](const char* name,TreeNode* root,bool expected){
        bool ok=isBalanced(root)==expected;
        std::cout<<name<<": "<<(ok?"PASS":"FAIL")<<'\n';
        if(!ok) ++failed;
    };
    check("empty",nullptr,true);
    check("single",&a2,true);
    check("balanced",&a1,true);
    check("unbalanced root",&b1,false);
    check("balanced root but unbalanced subtree",&deep,false);
    std::cout<<"Failed cases: "<<failed<<'\n';
    return failed==0?0:1;
}
