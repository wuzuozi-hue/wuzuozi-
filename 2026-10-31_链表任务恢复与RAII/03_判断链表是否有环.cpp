#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value) : val(value), next(nullptr) {}
};

// 判断指针连接是否形成环；不要修改链表。
bool hasCycle(ListNode* head) {
    // TODO：使用快慢指针，慢指针每次走一步，快指针每次走两步。
    // 提示：访问 fast->next->next 之前，先确保 fast 和 fast->next 非空。
    ListNode* fast =head;
    ListNode* slow = head;
    while(fast!=nullptr && fast->next!=nullptr){
        fast = fast->next->next;
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
    ListNode a(1), b(2), c(3), d(4);
    check("empty", nullptr, false);
    check("single", &a, false);
    a.next = &a;
    check("self-loop", &a, true);
    a.next = &b; b.next = &c; c.next = &d;
    check("no cycle", &a, false);
    d.next = &b;
    check("cycle", &a, true);
}
