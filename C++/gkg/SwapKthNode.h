#pragma once
#include "../Header.h"

class SwapKthNode {
public:
    static void test() {
        SwapKthNode obj;
        LinkedListNode<int>* head = Construct<int>({ 1,2,3,4,5 });
        cout << to_string(head);
        head = obj.swapNodes(head, 3);
        cout << to_string(head);
        head = obj.swapNodes(head, 4);
        cout << to_string(head);
        head = obj.swapNodes(head, 5);
        cout << to_string(head);
    }

    LinkedListNode<int>* swapNodes(LinkedListNode<int>* head, int k) {
        if (!head) return head;
        int l = length(head);
        if (l < k) return head;
        if (2 * k - 1 == l) return head;

        LinkedListNode<int>* prev1 = nullptr, * node1 = head;
        LinkedListNode<int>* prev2 = nullptr, * node2 = head;
        int i = 1;

        while (i < k) {
            prev1 = node1;
            node1 = node1->next;
            i++;
        }

        LinkedListNode<int>* tmp = node1->next;
        while (tmp) {
            prev2 = node2;
            node2 = node2->next;
            tmp = tmp->next;
        }

        if (prev1) prev1->next = node2;
        if (prev2) prev2->next = node1;

        swap(node1->next, node2->next);

        if (k == 1) return node2;
        else if (k == l) return node1;
        return head;
    }
};