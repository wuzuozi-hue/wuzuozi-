#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};
// 4 3 2 1
// 1 2 3 4
ListNode* reverseList(ListNode* head) {
    ListNode* cur = head;
    ListNode* prev = nullptr;
    while(cur!= nullptr){
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur =next;
    }
    return prev;
}

void check(const char* name, ListNode* head, const std::vector<int>& expected) {
    auto* p = reverseList(head);
    std::vector<int> actual;
    while (p && actual.size() <= expected.size()) {
        actual.push_back(p->val);
        p = p->next;
    }
    std::cout << name << ": " << (p == nullptr && actual == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, {});
    ListNode one(7);
    check("single", &one, {7});
    ListNode a(1), b(2), c(3), d(4);
    a.next = &b; b.next = &c; c.next = &d;
    check("four nodes", &a, {4, 3, 2, 1});
}
