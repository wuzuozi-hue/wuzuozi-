#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// a、b 是互不相交、升序的无环链表；复用节点并返回新头节点。
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if(a == nullptr){
        return b;
    }
    if(b == nullptr){
        return a;
    }
    ListNode* head;
   
    if(a->val<=b->val){
        head =a;
        a =a ->next;
    }else{
        head =b;
        b= b->next;
    }
    ListNode* tail = head;
    while(a!= nullptr && b!=nullptr){
        if(a->val <= b->val){
            tail->next = a;
            a = a->next;

        }else{
            tail->next =b;
            b = b->next; 
        }
        tail = tail->next;
    }
    if (a != nullptr) {
        tail->next = a;
    } 
    else {
        tail->next = b;
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
    ListNode a1(1), a2(3), a3(5), b1(2), b2(3), b3(6), b4(9);
    a1.next = &a2; a2.next = &a3;
    b1.next = &b2; b2.next = &b3; b3.next = &b4;
    check("different lengths and duplicates", &a1, &b1, {1, 2, 3, 3, 5, 6, 9});
}
