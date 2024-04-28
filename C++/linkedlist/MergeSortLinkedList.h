#pragma once
#include "../header.h"

class LinkedListMergeSort {
   public:
    static void test() {
        LinkedListMergeSort obj;
        vector<vector<int>> inputs = {
            {},
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4}};
        for (auto& input : inputs) {
            auto l = LinkedList<int>(input);
            obj.sort(l);
            cout << l << endl;
        }
    }

   public:
    void sort(LinkedList<int> head) {
        auto node = head.get_head();
        sort(node);
        head.set_head(node);
    }

    void sort(LinkedList<int>::Node* node) {
        if (node == nullptr || node->next == nullptr) return;
        LinkedList<int>::Node* first = nullptr;
        LinkedList<int>::Node* second = nullptr;

        split(node, first, second);
        sort(first);
        sort(second);

        node = merge(first, second);
    }

    void split(LinkedList<int>::Node* root, LinkedList<int>::Node*& first, LinkedList<int>::Node*& second) {
        first = root;
        LinkedList<int>::Node* slow = root;
        LinkedList<int>::Node* fast = root->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next;
        }

        second = slow->next;
        slow->next = nullptr;
    }

    LinkedList<int>::Node* merge(LinkedList<int>::Node* first, LinkedList<int>::Node* second) {
        if (!first) return second;
        if (!second) return first;

        LinkedList<int>::Node* result;
        if (first->val < second->val) {
            result = first;
            result->next = merge(first->next, second);
        } else {
            result = second;
            result->next = merge(first, second->next);
        }

        return result;
    }
};