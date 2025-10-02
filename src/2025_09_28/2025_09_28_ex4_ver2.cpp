#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

/*
    23. Merge k Sorted Lists
    You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
    Merge all the linked-lists into one sorted linked-list and return it.
    https://leetcode.com/problems/merge-k-sorted-lists/description/
*/

 // Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        ListNode* new_list = new ListNode(-1);

        if (lists.empty()) {
            return nullptr;
        }

        auto cmp = [] (ListNode* a, ListNode* b) { return a->val > b->val;  };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> max_priority_queue;

        for (const auto& list : lists) {
            if (list != nullptr) {
                max_priority_queue.push(list);
            }
           
        }
        // [[1,4,5],[1,3,4],[2,6]]
        ListNode* tail = &new_list[0];
        while (!max_priority_queue.empty()) {
            ListNode* top = max_priority_queue.top();
            max_priority_queue.pop();

            tail->next = top;
            tail = &tail->next[0];
            if (top->next) {
                max_priority_queue.push(top->next);
            }
            
        }

        return new_list->next;
    }

void Tests() {

    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(5);

    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);

    ListNode* l3 = new ListNode(2);
    l3->next = new ListNode(6);

    std::vector<ListNode*> lists;
    lists.push_back(l1);
    lists.push_back(l2);
    lists.push_back(l3);

    ListNode* list = mergeKLists(lists);

    ListNode* empty = nullptr;
    std::vector<ListNode*> empty_vector;
    empty_vector.push_back(empty);

    ListNode* expected_empty = mergeKLists(empty_vector);
    assert(expected_empty == empty);
}


int main() {
    Tests();

    return EXIT_SUCCESS;
}