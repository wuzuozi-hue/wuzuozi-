#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 链表升序，每个值只保留一个节点。仅调整连接，不 delete；调用者管理节点。
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while(cur!=nullptr && cur->next!=nullptr){
        if(cur->val == cur->next->val){
            cur->next = cur->next->next;
        }else{
            cur =cur->next;
        }
    }
    return head;
}

void check(const char* name, ListNode* head, const std::vector<int>& expected) {
    ListNode* p = deleteDuplicates(head);
    std::vector<int> actual;
    while (p && actual.size() <= expected.size()) {
        actual.push_back(p->val);
        p = p->next;
    }
    std::cout << name << ": " << (p == nullptr && actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    ListNode one(1); check("single", &one, {1});
    ListNode a(1), b(1), c(2), d(3), e(3), f(3);
    a.next = &b; b.next = &c; c.next = &d; d.next = &e; e.next = &f;
    check("duplicate groups", &a, {1, 2, 3});
    ListNode x(4), y(4), z(4); x.next = &y; y.next = &z;
    check("all same", &x, {4});
    ListNode m(1), n(2), o(3); m.next = &n; n.next = &o;
    check("no duplicates", &m, {1, 2, 3});
}
