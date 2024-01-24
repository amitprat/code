#pragma once
#include "../Header.h"

class ReverseEvenList {
public:
    static void test() {
        ReverseEvenList obj;
        LinkedListNode<int>* node = new LinkedListNode<int>(1);
        node->next = new LinkedListNode<int>(2);
        node->next->next = new LinkedListNode<int>(8);
        node->next->next->next = new LinkedListNode<int>(8);
        node->next->next->next->next = new LinkedListNode<int>(12);
        node->next->next->next->next->next = new LinkedListNode<int>(16);

        cout << to_string(node) << endl;

        LinkedListNode<int>* out = obj.reverse(node);
        cout << to_string(out) << endl;
    }

    LinkedListNode<int>* reverse(LinkedListNode<int>* head) {
        LinkedListNode<int>* cur = head;
        LinkedListNode<int>* prev = nullptr;

        while (cur) {
            if (!(cur->val & 1)) {
                if (prev) prev->next = reverseSub(cur);
                if (!prev) head = reverseSub(cur);
            }
            prev = cur;
            if (cur) cur = cur->next;
        }
        return head;
    }

    LinkedListNode<int>* reverseSub(LinkedListNode<int>*& cur) {
        LinkedListNode<int>* prev = nullptr;
        LinkedListNode<int>* oldCur = cur;

        while (cur && (!((cur->val) & 1))) {
            auto* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        oldCur->next = cur;
        return prev;
    }
};