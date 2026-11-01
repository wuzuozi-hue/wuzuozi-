#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 原地反转链表，返回新的头节点。
ListNode* reverseList(ListNode* head) {
    ListNode* cur = head;
    ListNode* prev =nullptr;
    while(cur!= nullptr){
        ListNode* next = cur->next;
        cur->next =prev;
        prev= cur;
        cur = next;
    }
    return prev; // 占位
}

void check(const char* name, ListNode* head, const std::vector<int>& expected) {
    ListNode* p = reverseList(head);
    std::vector<int> actual;
    // 最多走 expected.size()+1 步，避免错误成环时测试永久循环。
    while (p && actual.size() <= expected.size()) {
        actual.push_back(p->val);
        p = p->next;
    }
    std::cout << name << ": " << ((p == nullptr && actual == expected) ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    ListNode one(7);
    check("single", &one, {7});
    ListNode a(1), b(2), c(3), d(4);
    a.next = &b; b.next = &c; c.next = &d;
    check("four nodes", &a, {4, 3, 2, 1});
}
