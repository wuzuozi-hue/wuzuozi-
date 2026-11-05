#include <iostream>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

bool hasCycle(ListNode* head) {
    ListNode* fast = head;
    ListNode* slow =head;
    while(fast!=nullptr && fast->next!=nullptr){
        fast =fast->next->next;
        slow = slow->next;
        if(fast == slow){
            return true;
        }
    }
    return false;
}

void check(const char* name, ListNode* head, bool expected) {
    std::cout << name << ": " << (hasCycle(head) == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    check("empty", nullptr, false);
    ListNode a(1), b(2), c(2), d(4);
    check("single", &a, false);
    a.next = &a; check("self-loop", &a, true);
    a.next = &b; b.next = &c; c.next = &d;
    check("same values no cycle", &a, false);
    d.next = &b; check("cycle", &a, true);
    d.next = &a; check("cycle at head", &a, true);
}
