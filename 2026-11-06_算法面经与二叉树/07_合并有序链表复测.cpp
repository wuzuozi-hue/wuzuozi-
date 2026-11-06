#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 合并两个升序链表，返回合并后链表的头节点。
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if(a == nullptr){
        return b;
    }
    if(b == nullptr){
        return a;
    }
    ListNode * tail;
    if(a->val <= b->val){
        tail = a;
        a = a->next;
    }else{
        tail = b;
        b = b->next;
    }
    ListNode* head =tail;
    while(a!=nullptr && b!=nullptr){
        if(a->val <= b->val){
            tail->next = a;
            a = a->next;
        }else{
            tail ->next =b;
            b = b->next;
        }
        tail = tail->next;
    }
    if(a ==nullptr){
        tail->next = b;
        tail =tail->next;
    }else{
        tail->next =a;
        tail = tail->next;
    }
    return head;
}

void check(const char* name, ListNode* head, const std::vector<int>& expected) {
    std::vector<int> actual;
    // 限制遍历长度，避免错误实现形成环时测试一直运行。
    while (head && actual.size() <= expected.size()) {
        actual.push_back(head->val);
        head = head->next;
    }
    std::cout << name << ": " << (actual == expected && !head ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("both empty", mergeTwoLists(nullptr, nullptr), {});
    ListNode x(2);
    check("one empty", mergeTwoLists(&x, nullptr), {2});
    ListNode a(1), b(3), c(5), d(2), e(4), f(6);
    a.next = &b; b.next = &c; d.next = &e; e.next = &f;
    check("interleaved", mergeTwoLists(&a, &d), {1, 2, 3, 4, 5, 6});
    ListNode g(1), h(1), i(2);
    g.next = &i;
    check("duplicates", mergeTwoLists(&g, &h), {1, 1, 2});
}
