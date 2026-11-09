#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(v), left(l), right(r) {}
};

// LeetCode 257（Easy，新题）：返回所有从根节点到叶子节点的路径。
// 叶子节点：左右孩子都为空的节点。路径用 "->" 连接，可任意顺序返回。
//       1
//      / \
//     2   3
//      \
//       5
// 返回 {"1->2->5", "1->3"}。空树返回空数组。
// 思路：递归时携带当前路径，遇到叶子节点时把路径放进结果。
// 可自行添加辅助函数；std::to_string(node->val) 可把数值转成字符串。
void dfs(TreeNode* node,std::string path,std::vector<std::string>& result){
    if(node == nullptr){
        return;
    }
    if(node != nullptr){
        path +=std::to_string(node->val);
    }
    if(node->left == nullptr && node->right == nullptr){
        result.push_back(path);
        return ;
    }else{
        path +="->";
    }
    dfs(node->left,path,result);
    dfs(node->right,path,result);
}
std::vector<std::string> binaryTreePaths(TreeNode* root) {
    std::vector<std::string> result;
    dfs(root,"",result);
    return result;
}

int main() {
    TreeNode n5(5),n2(2,nullptr,&n5),n3(3),n1(1,&n2,&n3);
    TreeNode neg(-2),single(7),r3(3),r2(2,nullptr,&r3),r1(1,nullptr,&r2);
    int failed=0;
    auto check=[&](const char* name, TreeNode* root, std::vector<std::string> expected){
        auto actual=binaryTreePaths(root);
        std::sort(actual.begin(),actual.end());
        std::sort(expected.begin(),expected.end());
        bool ok=actual==expected;
        std::cout<<name<<": "<<(ok?"PASS":"FAIL")<<'\n';
        if(!ok) ++failed;
    };
    check("empty",nullptr,{});
    check("example",&n1,{"1->2->5","1->3"});
    check("single",&single,{"7"});
    check("negative",&neg,{"-2"});
    check("chain",&r1,{"1->2->3"});
    std::cout<<"Failed cases: "<<failed<<'\n';
    return failed==0?0:1;
}
