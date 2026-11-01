#include <iostream>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int v) : val(v) {}
};

// 输入为无环链表；返回第一个公共节点的指针，不相交返回 nullptr。
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    // TODO：实现相交链表；比较节点指针，不要只比较 val。
    ListNode* a = headA;
    ListNode* b = headB;
    while(a !=b){
       if(a ==nullptr){
        a =headB;
       }
       else{
        a = a->next;
       }
       if(b == nullptr){
        b =headA;
       }else{
        b = b->next;
       }
    }
    return a;
}

void check(const char* name, ListNode* a, ListNode* b, ListNode* expected) {
    std::cout << name << ": " << (getIntersectionNode(a, b) == expected ? "PASS" : "FAIL") << '\n';
}

int main() {
    ListNode a(1), b(2), c(3), x(9), y(8), z(3);
    a.next = &b; b.next = &c; x.next = &c;
    check("different lengths", &a, &x, &c);
    check("same head", &a, &a, &a);
    check("one empty", nullptr, &a, nullptr);
    y.next = &z; // z 的值与 c 相同，但不是同一个节点。
    check("same value no intersection", &a, &y, nullptr);
    check("both empty", nullptr, nullptr, nullptr);
}
