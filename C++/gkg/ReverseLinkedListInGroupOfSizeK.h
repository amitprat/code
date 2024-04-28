#pragma once
#include "../header.h"

class ReverseLinkedListInGroupOfSizeK {
    using Node = LinkedList<int>::Node;

   public:
    Node *reverseList(Node *head, int k) {
        Node *tmp = head;
        Node *prev = nullptr;

        int cnt = 0;
        while (cnt++ < k && tmp) {
            auto next = tmp->next;
            tmp->next = prev;
            prev = tmp;
            tmp = next;
        }

        if (tmp) {
            head->next = reverseList(tmp, k);
        }

        return prev;
    }
};