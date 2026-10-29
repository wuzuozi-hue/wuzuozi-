#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <vector>

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};

// 输入两条升序、无环且互不共享节点的链表。
// 通过连接原来的节点得到一条升序链表，不创建额外的数据节点。
// 例如a: 2->6->9，b: 1->4->8，返回1->2->4->6->8->9。
ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
    ListNode dummy(0);       // 哨兵：只作为接链表的起点，不属于答案。
    ListNode* tail = &dummy; // tail始终指向结果链表的最后一个节点。

    // TODO 1：当a和b都非空时，比较它们的val。
    // TODO 2：将较小的节点接到tail后面，并推进对应的a或b。
    // TODO 3：每轮推进tail，使它指向刚接入的节点。
    // TODO 4：一条用完后，接上另一条剩余部分。
    // TODO 5：返回dummy.next。
    while(a!= nullptr && b !=nullptr){
        if(a->val <= b->val){
            tail->next = a;
            a = a->next;
        }
        else{
            tail->next = b;
            b= b->next;
        }
        tail = tail->next;
    }
    while(a!=nullptr){
        tail->next = a;
        a = a->next;
        tail = tail->next;
    }
    while(b!=nullptr){
        tail->next = b;
        b = b->next;
        tail = tail->next;
    }
    return dummy.next;
}

// 以下测试区不需要修改，测试区统一持有并释放节点。
int main() {
    struct Case { std::vector<int> a; std::vector<int> b; };
    const std::vector<Case> cases{
        {{2, 6, 9}, {1, 4, 8}}, {{}, {}}, {{}, {3, 7}},
        {{1, 5}, {}}, {{2, 2, 7}, {2, 4}},
        {{-5, -1, 6}, {-3, 0}}, {{1, 3, 5, 7}, {2}}
    };
    int passed = 0;
    for (std::size_t t = 0; t < cases.size(); ++t) {
        std::vector<std::unique_ptr<ListNode>> owners;
        const auto makeList = [&](const std::vector<int>& values) {
            ListNode* head = nullptr;
            ListNode* last = nullptr;
            for (int value : values) {
                owners.push_back(std::make_unique<ListNode>(value));
                auto node = owners.back().get();
                if (last) last->next = node;
                else head = node;
                last = node;
            }
            return head;
        };
        ListNode* a = makeList(cases[t].a);
        ListNode* b = makeList(cases[t].b);
        std::unordered_set<ListNode*> remaining;
        for (const auto& p : owners) remaining.insert(p.get());
        auto expected = cases[t].a;
        expected.insert(expected.end(), cases[t].b.begin(), cases[t].b.end());
        std::sort(expected.begin(), expected.end());
        try {
            ListNode* cursor = mergeTwoLists(a, b);
            bool ok = true;
            for (int value : expected) {
                if (!cursor || remaining.erase(cursor) != 1) {
                    ok = false;
                    break;
                }
                if (cursor->val != value) ok = false;
                cursor = cursor->next;
            }
            if (cursor || !remaining.empty()) ok = false;
            for (std::size_t i = 0; i < cases[t].a.size(); ++i) {
                if (owners[i]->val != cases[t].a[i]) ok = false;
            }
            for (std::size_t i = 0; i < cases[t].b.size(); ++i) {
                if (owners[cases[t].a.size() + i]->val != cases[t].b[i]) ok = false;
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
