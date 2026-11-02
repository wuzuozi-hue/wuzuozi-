#include <iostream>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 返回倒数第 k 个节点；如果 k <= 0 或长度不足，返回 nullptr。
ListNode* kthFromEnd(ListNode* head, int k) {
    // 在这里实现。
    ListNode* fast =head;
    ListNode* slow =head;
    if(k <=0){
        return nullptr;
    }
    for(int i = 0;i<k;i++){
        if(fast == nullptr){
            return nullptr;
        }
        fast =fast->next;
    }
    while(fast!=nullptr){
        fast= fast->next;
        slow =slow->next;
    }
  
    return slow;
}

void check(const char* name, ListNode* result, ListNode* expected) {
    std::cout << name << ": " << (result == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    ListNode a(1), b(2), c(3), d(4), e(5);
    a.next = &b; b.next = &c; c.next = &d; d.next = &e;
    check("second from end", kthFromEnd(&a, 2), &d);
    check("tail", kthFromEnd(&a, 1), &e);
    check("head", kthFromEnd(&a, 5), &a);
    check("too long", kthFromEnd(&a, 6), nullptr);
    check("zero", kthFromEnd(&a, 0), nullptr);
    check("empty", kthFromEnd(nullptr, 1), nullptr);
}
