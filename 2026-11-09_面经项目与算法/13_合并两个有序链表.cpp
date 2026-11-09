#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int v, ListNode* n = nullptr) : val(v), next(n) {}
};

// LeetCode 21（Easy，复测）
// 输入两个升序单链表，将原节点连接成一个升序链表并返回头节点。
// 不要求新建节点；两个输入链表互不相交，可以为空。
// 例：1 -> 3 -> 5 和 2 -> 4 -> 6
// 合并后：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    if(a == nullptr){
        return b;
    }
    if(b == nullptr){
        return a;
    }
    ListNode* tail;
    if(a->val <= b->val){
        tail = a;
        a = a ->next;
    }else{
        tail = b;
        b = b->next;
    }
    ListNode* head =tail;
    while(a!=nullptr && b!=nullptr){
        if(a->val <=b->val){
            tail ->next = a;
            a =a->next;
        }else{
            tail->next =b;
            b=b->next;
        }
        tail = tail->next;
    }
    if(a == nullptr){
        tail->next =b;
        tail = tail->next;
    }else{
        tail->next = a;
        tail = tail->next;
    }
    return head;


}

int main() {
    int failed = 0;
    auto check = [&](const char* name, ListNode* a, ListNode* b, const std::vector<int>& expected) {
        ListNode* node = mergeTwoLists(a, b);
        std::vector<int> actual;
        // 限制遍历，避免错误的环使测试一直运行。
        while (node && actual.size() <= expected.size()) {
            actual.push_back(node->val);
            node = node->next;
        }
        bool ok = node == nullptr && actual == expected;
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        if (!ok) ++failed;
    };
    ListNode a3(5),a2(3,&a3),a1(1,&a2), b3(6),b2(4,&b3),b1(2,&b2);
    check("interleaved", &a1, &b1, {1,2,3,4,5,6});
    check("both empty", nullptr, nullptr, {});
    ListNode c2(4),c1(1,&c2);
    check("one empty", &c1, nullptr, {1,4});
    ListNode d2(2),d1(1,&d2),e2(3),e1(2,&e2);
    check("duplicate values", &d1, &e1, {1,2,2,3});
    ListNode f3(5),f2(4,&f3),f1(3,&f2),g1(1);
    check("unequal lengths", &f1, &g1, {1,3,4,5});
    std::cout << "Failed cases: " << failed << '\n';
    return failed == 0 ? 0 : 1;
}
