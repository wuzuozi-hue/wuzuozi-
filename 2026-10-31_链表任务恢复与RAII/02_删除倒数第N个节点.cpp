#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value) : val(value), next(nullptr) {}
};

// 已知链表非空，且 1 <= n <= 链表长度。
// 只调整指针，不在此函数内 delete 节点；测试代码负责节点的生命周期。
ListNode* removeNthFromEnd(ListNode* head, int n) {
    // 练习：让 fast 先走 n 步，再让 fast 和 slow 配合找到要删除的节点。
    // 可以自行选择使用 dummy 节点或单独处理删除头节点。
    ListNode* fast = head;
    ListNode* slow = head;
    if(head == nullptr){
        return nullptr;
    }
 
    for(int i = 0; i<n; i++){
        fast = fast->next;
    }
       if(fast == nullptr){
        return head->next;
    }
    while(fast->next != nullptr){
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    return head;
}

void runTest(const std::vector<int>& values, int n,
             const std::vector<int>& expected) {
    std::vector<ListNode*> nodes;
    for (int value : values) nodes.push_back(new ListNode(value));
    for (std::size_t i = 1; i < nodes.size(); ++i) nodes[i - 1]->next = nodes[i];
    ListNode* result = removeNthFromEnd(nodes.front(), n);
    std::vector<int> actual;
    for (ListNode* p = result; p != nullptr; p = p->next) actual.push_back(p->val);
    std::cout << (actual == expected ? "PASS" : "FAIL") << '\n';
    for (ListNode* node : nodes) delete node;
}

int main() {
    runTest({1, 2, 3, 4, 5}, 2, {1, 2, 3, 5});
    runTest({1, 2, 3}, 3, {2, 3});
    runTest({1, 2, 3}, 1, {1, 2});
    runTest({7}, 1, {});
}
