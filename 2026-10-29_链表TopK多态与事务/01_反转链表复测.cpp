#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 今天的数据：6 -> 2 -> 8 -> nullptr。
//            8    2    6    nullptr
// 初始：prev = nullptr，cur指向6。
// 先手推两轮，填下面的注释，再写函数；先不看昨天的实现。
// 第一轮结束：prev指向____，cur指向____。
// 第二轮结束：prev指向____，cur指向____。
// 然后说明：为什么修改next前需要保存原来的后继？

// 任务：原地反转节点连接，返回新头节点；节点中的数字不变。
// 空链表返回nullptr，单节点返回原节点。
ListNode* reverseList(ListNode* head) {
    // 在这里写你的循环版。实现后删除下面两行占位代码。
    ListNode* prev =nullptr;
    ListNode* cur = head;
    while(cur != nullptr){
        ListNode* nextnode = cur->next;
        cur->next =prev;
        prev = cur;
        cur =nextnode;
    }
    return prev;
}

// 以下测试区不用修改，内存由测试区管理。
int main() {
    const std::vector<std::vector<int>> cases{
        {6, 2, 8}, {}, {5}, {7, 3}, {2, 2, 5, 2}, {0, -4, 9, -1}
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
