// 2026-11-07 | LeetCode 21 | 简单 | 复测 | 状态：未开始
// 题意：把两条非递减的单链表合并为一条非递减链表，返回表头。
// 输入：两条互不共享节点、无环的链表，可为空。输出：合并后的表头。
// 本练习要求复用全部原节点，允许改 next，不创建或删除数据节点，不修改 val。
// 边界：两空、一空、重复值、长度不同；结果必须以 nullptr 结尾且无环。
// 测试节点都在栈上，请勿 delete；若使用哑节点，不能把它作为结果节点返回。
// 只替换 TODO；编译通过不代表掌握，未实现时应有测试失败。
#include <iostream>
#include <unordered_set>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

ListNode* mergeTwoLists(ListNode* listA, ListNode* listB) {
    ListNode* cur;
    if(listA == nullptr){
        return listB;
    }
    if(listB == nullptr){
        return listA;
    }
    if(listA ->val <= listB->val){
        cur = listA;
        listA = listA->next;
    }else{
        cur =listB;
        listB = listB->next;
    }
    ListNode* head = cur;
    while(listA!=nullptr &&listB != nullptr){
        if(listA ->val <= listB->val){
            cur->next = listA;
            listA = listA->next;
        }else{
            cur->next = listB;
            listB = listB->next;
        }
        cur = cur->next;
    }
    if(listA == nullptr){
        cur->next = listB;
        cur = cur->next;
    }else{
        cur->next = listA;
        cur = cur->next;
    }
    return head;
}

// 先验证地址来源，再解引用；visited 防止错误结果形成环时无限遍历。
bool matches(ListNode* head, const std::vector<int>& expected,
             const std::vector<ListNode*>& originalNodes) {
    std::unordered_set<ListNode*> allowed(originalNodes.begin(), originalNodes.end());
    std::unordered_set<ListNode*> visited;
    std::vector<int> actual;
    while (head) {
        if (allowed.count(head) == 0 || !visited.insert(head).second) return false;
        actual.push_back(head->val);
        head = head->next;
    }
    return actual == expected && visited.size() == allowed.size();
}

int main() {
    int failures = 0;
    auto check = [&](const char* name, ListNode* list1, ListNode* list2,
                     const std::vector<int>& expected, const std::vector<ListNode*>& nodes) {
        std::vector<int> beforeValues;
        for (ListNode* node : nodes) beforeValues.push_back(node->val);
        ListNode* result = mergeTwoLists(list1, list2);
        bool ok = matches(result, expected, nodes);
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            if (nodes[i]->val != beforeValues[i]) ok = false;
        }
        std::cout << name << ": " << (ok ? "PASS" : "FAIL") << '\n';
        failures += !ok;
    };
    check("both empty", nullptr, nullptr, {}, {});
    ListNode a(0);
    check("first empty", nullptr, &a, {0}, {&a});
    ListNode b(-2), c(3);
    b.next = &c;
    check("second empty", &b, nullptr, {-2, 3}, {&b, &c});
    ListNode d(1), e(2), f(4), g(1), h(3), i(4);
    d.next = &e; e.next = &f; g.next = &h; h.next = &i;
    check("interleaving duplicates", &d, &g, {1, 1, 2, 3, 4, 4}, {&d, &e, &f, &g, &h, &i});
    ListNode j(-5), k(-3), l(0), m(7);
    j.next = &k; k.next = &l;
    check("unequal lengths", &j, &m, {-5, -3, 0, 7}, {&j, &k, &l, &m});
    ListNode n(9), o(2);
    check("second head comes first", &n, &o, {2, 9}, {&n, &o});
    std::cout << "Failed cases: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
