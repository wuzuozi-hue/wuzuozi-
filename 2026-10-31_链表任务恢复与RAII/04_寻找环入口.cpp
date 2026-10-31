#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value) : val(value), next(nullptr) {}
};

ListNode* detectCycle(ListNode* head) {
    // 阶段一：像上一题一样，快慢指针分别走两步、一步。
    // 没有环就返回 nullptr；有环则找到两个指针的相遇节点。
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast!=nullptr&&fast->next!=nullptr){
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow){
            break;
        }
    }
    if(fast==nullptr || fast->next == nullptr){
        return nullptr;
    }
    fast =head;
    while(fast !=slow){
        fast = fast->next;
        slow =slow->next;
    }
    return fast;
}

void check(const char* name, ListNode* head, ListNode* expected) {
    std::cout << name << ": " << (detectCycle(head) == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    ListNode a(1), b(2), c(3), d(4), e(5);
    check("empty", nullptr, nullptr);
    check("single", &a, nullptr);
    a.next = &a;
    check("self-loop", &a, &a);
    a.next = &b; b.next = &c; c.next = &d; d.next = &e;
    check("no cycle", &a, nullptr);
    e.next = &c;
    check("entry at 3", &a, &c);
    e.next = &a;
    check("entry at head", &a, &a);
}
