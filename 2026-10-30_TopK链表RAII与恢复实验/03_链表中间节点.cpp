#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 返回链表的中间节点；偶数长度返回靠后的那个中点。
// 1->2->3->4->5 返回节点3；1->2->3->4 返回节点3。
// 空链表返回nullptr；不修改原链表的节点和连接。
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    if(head == nullptr){
        return nullptr;
    }
    while(fast != nullptr && fast->next != nullptr){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;

}

// 测试区不用修改。测试区拥有节点，函数只返回一个观察指针。
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
        ListNode* expected = nodes.empty() ? nullptr : nodes[nodes.size() / 2].get();
        try {
            ListNode* actual = middleNode(head);
            bool ok = actual == expected;
            for (std::size_t i = 0; i < nodes.size(); ++i) {
                ListNode* expectedNext = i + 1 < nodes.size() ? nodes[i + 1].get() : nullptr;
                if (nodes[i]->val != cases[t][i] || nodes[i]->next != expectedNext) ok = false;
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
