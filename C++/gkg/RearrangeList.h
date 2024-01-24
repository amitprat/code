#pragma once
#include "../Header.h"

class RearrangeList {
public:
    static void test() {
        RearrangeList obj;
        LinkedListNode<int>* root = Create<int>({ 1,2,3 });
        cout << to_string(root) << endl;

        root = obj.rearrange(root);

        cout << to_string(root) << endl;
    }

    LinkedListNode<int>* rearrange(LinkedListNode<int>* root) {
        LinkedListNode<int>* first = nullptr, * second = nullptr;
        split(root, first, second);
        if (second == nullptr || first->next == second) return root;

        while (second) {
            auto next = first->next;
            first->next = second;
            second = second->next;
            first->next->next = next;
            first = next;
        }

        return root;
    }

    void split(LinkedListNode<int>* root, LinkedListNode<int>*& first, LinkedListNode<int>*& second) {
        first = root;
        second = root->next;
        while (second && second->next) {
            first = first->next;
            second = second->next->next;
        }

        second = first->next;
        first->next = nullptr;

        first = root;

        cout << "First List After Split: " << to_string(first) << endl;
        cout << "Second List After Split: " << to_string(second) << endl;
    }
};