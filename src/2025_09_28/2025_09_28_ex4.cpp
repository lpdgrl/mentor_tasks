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
        ListNode* new_list = nullptr;

        auto cmp = [] (int a, int b) { return a > b; };
        std::priority_queue<int, std::vector<int>, decltype(cmp)> max_priority_queue;
        size_t size_queue = 0;
        
        ListNode* ptr_iter = nullptr;

        for (const auto& list :lists) {
            if (list == nullptr) { 
                continue;
            }
            
            max_priority_queue.push(list->val);
            ptr_iter = list->next;
            ++size_queue;
            while (ptr_iter != nullptr) {
                max_priority_queue.push(ptr_iter->val);
                ptr_iter = ptr_iter->next;
                ++size_queue;
            }
        }

        ptr_iter = nullptr;
        if (max_priority_queue.size() > 0) {
            new_list = new ListNode(max_priority_queue.top());
            max_priority_queue.pop();
            ptr_iter = new_list;
            for (size_t i = 0; i < size_queue - 1; ++i) {
                ptr_iter->next = new ListNode(max_priority_queue.top());
                max_priority_queue.pop();
                ptr_iter = ptr_iter->next;
            }
        }
  
        return new_list;
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