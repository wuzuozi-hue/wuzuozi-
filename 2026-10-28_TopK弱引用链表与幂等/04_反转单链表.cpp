#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

// 一个节点包含：自己的数字，以及指向下一个节点的指针。
struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 只阅读这个示例：a -> b -> c -> nullptr。
void showNodes() {
    ListNode a(4);
    ListNode b(7);
    ListNode c(9);
    a.next = &b;
    b.next = &c;
    ListNode* head = &a;
    std::cout << "head value: " << head->val << '\n';
    std::cout << "next value: " << head->next->val << '\n';
}

// 题目：原地反转链表，返回新的头节点。不修改节点中的数字。
// 例如：4 -> 7 -> 9 -> nullptr，变成9 -> 7 -> 4 -> nullptr。
// 空链表返回nullptr；单节点仍返回该节点。
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;

    while (cur != nullptr) {
        ListNode* nextNode = cur->next; // 保存后路
        cur->next = prev;              // 反转当前指向

        prev = cur; // 让 prev 指向刚处理完的节点
        cur = nextNode;  // 让 cur 走向保存好的后续节点
    }

    return prev;
}

// 以下是测试区，不需要修改。测试区统一拥有并释放节点。
int main() {
    showNodes();
    const std::vector<std::vector<int>> cases{
        {}, {6}, {4, 7}, {4, 7, 9}, {2, 2, 5, 2}
    };
    int passed = 0;
    for (std::size_t t = 0; t < cases.size(); ++t) {
        std::vector<std::unique_ptr<ListNode>> nodes;
        for (int value : cases[t]) {
            nodes.push_back(std::make_unique<ListNode>(value));
        }
        for (std::size_t i = 1; i < nodes.size(); ++i) {
            nodes[i - 1]->next = nodes[i].get();
        }
        ListNode* head = nodes.empty() ? nullptr : nodes.front().get();
        try {
            ListNode* cursor = reverseList(head);
            bool ok = true;
            for (std::size_t i = 0; i < nodes.size(); ++i) {
                // 验证节点身份与顺序，不能仅通过交换数字假装反转。
                if (cursor != nodes[nodes.size() - 1 - i].get()) {
                    ok = false;
                    break;
                }
                cursor = cursor->next;
            }
            if (cursor != nullptr) ok = false;
            for (std::size_t i = 0; i < nodes.size(); ++i) {
                if (nodes[i]->val != cases[t][i]) ok = false;
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
