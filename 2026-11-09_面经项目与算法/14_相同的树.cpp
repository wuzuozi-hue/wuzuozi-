#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 100（Easy）：给定两棵二叉树，判断它们是否相同。
// 相同要求：对应位置的结构相同，并且对应节点的值相同。
// 示例一：两棵树都是   1    返回 true
//                    / \
//                   2   3
// 示例二：    1       1     返回 false（结构不同）
//            /         \
//           2           2
// 两棵空树相同，一棵空另一棵非空则不同。
// 每次比较两个对应节点，再处理它们各自的左右子树。
bool isSameTree(TreeNode* p, TreeNode* q) {
    if(p == nullptr && q == nullptr){
        return true;
    }
    if((p ==nullptr && q!=nullptr) || (q==nullptr &&p!= nullptr)){
        return false;
    }
    
    if(p->val != q->val){
        return false;
    }
    bool left = isSameTree(p->left,q->left);
    bool right = isSameTree(p->right,q->right);
    return left&&right;
}

int main() {
    TreeNode a2(2),a3(3),a1(1,&a2,&a3);
    TreeNode b2(2),b3(3),b1(1,&b2,&b3);
    TreeNode c2(2),c1(1,&c2),d2(2),d1(1,nullptr,&d2);
    TreeNode e2(2),e4(4),e1(1,&e2,&e4);
    int failed = 0;
    auto check = [&](const char* name, TreeNode* p, TreeNode* q, bool expected) {
        bool actual = isSameTree(p,q);
        bool ok = actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) ++failed;
    };
    check("both empty", nullptr, nullptr, true);
    check("one empty", &a1, nullptr, false);
    check("equal trees", &a1, &b1, true);
    check("different shape", &c1, &d1, false);
    check("different value", &a1, &e1, false);
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
