#pragma once
#include "../Header.h"

// https://www.careercup.com/question?id=5723406763294720

class AddLinkedLists {
public:
    static void test() {
        LinkedListNode<int>* root1 = Create<int>({ 9,9,9,5, 6, 3 });
        LinkedListNode<int>* root2 = Create<int>({ 9,4, 3 });

        LinkedListNode<int>* root = add(root1, root2);
        cout << to_string(root) << endl;
    }

    static LinkedListNode<int>* add(LinkedListNode<int>* root1, LinkedListNode<int>* root2) {
        int l1 = length<int>(root1);
        int l2 = length<int>(root2);
        if (l1 > l2) { swap(root1, root2); swap(l1, l2); }
        int diff = l2 - l1;
        while (diff--) {
            LinkedListNode<int>* newNode = new LinkedListNode<int>(0);
            newNode->next = root1;
            root1 = newNode;
        }

        int carry = 0;
        LinkedListNode<int>* root = add(root1, root2, carry);
        if (carry) {
            LinkedListNode<int>* newNode = new LinkedListNode<int>(carry);
            newNode->next = root;
            root = newNode;
        }

        return root;
    }

    static LinkedListNode<int>* add(LinkedListNode<int>* root1, LinkedListNode<int>* root2, int& carry) {
        if (!root1 || !root2) return nullptr;
        if (isEnd(root1) && isEnd(root2)) {
            auto val = root1->val + root2->val;
            carry = val / 10;
            return new LinkedListNode<int>(val % 10);
        }

        auto next = add(root1->next, root2->next, carry);
        auto val1 = root1->val + root2->val + carry;
        carry = val1 / 10;
        auto cur = new LinkedListNode<int>(val1 % 10);
        cur->next = next;

        return cur;
    }

    static bool isEnd(LinkedListNode<int>* root) {
        return !root->next;
    }
};