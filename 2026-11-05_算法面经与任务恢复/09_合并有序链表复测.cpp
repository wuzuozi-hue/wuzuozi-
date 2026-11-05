#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 两条输入链表升序、无环且不相交。复用原节点并返回结果头节点。
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if( a== nullptr){
        return b;
    }
    if(b == nullptr){
        return a;
    }
    ListNode* tail;
    if(a->val <= b->val){
        tail = a;
        a= a->next;
    }
    else{
        tail = b;
        b = b->next;
    }
    ListNode* head = tail;
    while(a!=nullptr && b!=nullptr){
        if(a->val <=b->val){
            tail->next = a;
            a = a->next;
        }else{
            tail->next = b;
            b= b->next;
        }
        tail = tail->next;
    }
    if(a!= nullptr){
        tail ->next = a;
    }else{
        tail->next =b;
    }
    return head;
}

void check(const char* name, ListNode* a, ListNode* b, const std::vector<int>& expected) {
    ListNode* p = mergeTwoLists(a, b);
    std::vector<int> actual;
    while (p && actual.size() <= expected.size()) {
        actual.push_back(p->val);
        p = p->next;
    }
    std::cout << name << ": " << (p == nullptr && actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("both empty", nullptr, nullptr, {});
    ListNode one(4);
    check("one empty", &one, nullptr, {4});
    ListNode a(1), b(3), c(5), x(2), y(3), z(6), w(9);
    a.next = &b; b.next = &c; x.next = &y; y.next = &z; z.next = &w;
    check("different lengths and duplicates", &a, &x, {1, 2, 3, 3, 5, 6, 9});
}
