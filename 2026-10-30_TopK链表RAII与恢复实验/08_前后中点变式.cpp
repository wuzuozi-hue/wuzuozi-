#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 输入是无环单链表。空链表返回nullptr，不修改原节点与连接。
// 偶数长度：middleFirst返回前一个中点，middleSecond返回后一个中点。
// 例如1->2->3->4：前一个是2，后一个是3。
// 奇数长度：两个函数都返回同一个中点。

ListNode* middleSecond(ListNode* head) {
    // 偶数长度返回后一个中点。
    ListNode* fast = head;
    ListNode* slow = head;
    if(head == nullptr){
        return nullptr;
    }
    while(fast!= nullptr && fast->next!=nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

ListNode* middleFirst(ListNode* head) {
    // 偶数长度返回前一个中点。
    if(head == nullptr){
        return nullptr;
    }
    ListNode* fast = head->next;
    ListNode* slow = head;

    while(fast!= nullptr && fast->next!=nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// 以下测试区不用修改。
int main() {
    const std::vector<std::vector<int>> cases{
        {}, {7}, {4, 9}, {1, 2, 3}, {1, 2, 3, 4},
        {6, 2, 8, 4, 10}, {0, -2, 3, 4, 5, 6}, {2, 2, 2, 2}
    };
    int passed = 0;
    for (std::size_t t = 0; t < cases.size(); ++t) {
        std::vector<std::unique_ptr<ListNode>> nodes;
        for (int value : cases[t]) nodes.push_back(std::make_unique<ListNode>(value));
        for (std::size_t i = 1; i < nodes.size(); ++i) nodes[i - 1]->next = nodes[i].get();
        ListNode* head = nodes.empty() ? nullptr : nodes.front().get();
        ListNode* expectedFirst = nodes.empty() ? nullptr : nodes[(nodes.size() - 1) / 2].get();
        ListNode* expectedSecond = nodes.empty() ? nullptr : nodes[nodes.size() / 2].get();
        try {
            ListNode* first = middleFirst(head);
            ListNode* second = middleSecond(head);
            bool ok = first == expectedFirst && second == expectedSecond;
            for (std::size_t i = 0; i < nodes.size(); ++i) {
                ListNode* next = i + 1 < nodes.size() ? nodes[i + 1].get() : nullptr;
                if (nodes[i]->val != cases[t][i] || nodes[i]->next != next) ok = false;
            }
            if (ok) ++passed;
            std::cout << "case " << t + 1 << ": " << (ok ? "PASS" : "FAIL") << '\n';
        } catch (const std::exception& e) {
            std::cout << "case " << t + 1 << ": " << e.what() << '\n';
        }
    }
    std::cout << passed << '/' << cases.size() << " passed\n";
    return passed == static_cast<int>(cases.size()) ? 0 : 1;
}
