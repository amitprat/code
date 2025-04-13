#pragma once
#include "../design/Set.h"
#include "../header.h"
#include "LinkedList.h"

class RemoveDuplicates {
    using Node = LinkedList<int>::Node;

   public:
    static void test() {
        RemoveDuplicates obj;

        std::vector<std::vector<int>> testCases = {
            {}, {1}, {1, 1}, {1, 1, 2}, {1, 2, 3}, {1, 2, 3, 3, 3}, {1, 1, 2, 2, 3, 3}};

        for (const auto& vals : testCases) {
            LinkedList<int> list(vals);
            std::cout << "Original List: " << list.to_string() << '\n';
            obj.removeDupsSorted(list);  // Choose one
            std::cout << "After Removal: " << list.to_string() << '\n';
        }
    }

    // Remove all duplicates from sorted list (no duplicates remain)
    void removeDupsSorted(LinkedList<int>& list) {
        Node dummy{-1};
        dummy.next = list.getHead();
        Node* prev = &dummy;

        while (prev->next) {
            Node* cur = prev->next;
            bool duplicate = false;
            while (cur->next && cur->val == cur->next->val) {
                Node* temp = cur->next;
                cur->next = temp->next;
                delete temp;
                duplicate = true;
            }
            if (duplicate) {
                Node* temp = prev->next;
                prev->next = cur->next;
                delete temp;
            } else {
                prev = prev->next;
            }
        }
        list.setHead(dummy.next);
    }

    // Keep one copy of each element in sorted list
    void removeDupsKeepOneSorted(LinkedList<int>& list) {
        Node* cur = list.getHead();
        while (cur && cur->next) {
            if (cur->val == cur->next->val) {
                Node* tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
    }

    // Keep one copy of each element (unsorted list)
    void removeDupsUnsorted(LinkedList<int>& list) {
        if (list.empty()) return;

        std::unordered_set<int> seen;
        Node* cur = list.getHead();
        seen.insert(cur->val);

        while (cur->next) {
            if (seen.contains(cur->next->val)) {
                Node* tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
            } else {
                seen.insert(cur->next->val);
                cur = cur->next;
            }
        }
    }
};