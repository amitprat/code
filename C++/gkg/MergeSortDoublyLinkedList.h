#pragma once
#include "../Header.h"

class MergeSortDoublyLinkedList {
public:
    static void test() {
        MergeSortDoublyLinkedList obj;
        LinkedListNode<int>* root = new LinkedListNode<int>(5);
        root->next = new LinkedListNode<int>(20);
        root->next->prev = root;
        root->next->next = new LinkedListNode<int>(4);
        root->next->next->prev = root;
        root->next->next->next = new LinkedListNode<int>(3);
        root->next->next->next->prev = root;
        root->next->next->next->next = new LinkedListNode<int>(30);
        root->next->next->next->next->prev = root;
        root->next->next->next->next->next = new LinkedListNode<int>(10);
        root->next->next->next->next->next->prev = root;

        cout << "List: " << to_string(root) << endl;
        auto res = obj.mergeSort(root);

        cout << "Sorted List: " << to_string(res) << endl;
    }

    LinkedListNode<int>* mergeSort(LinkedListNode<int>* root) {
        LinkedListNode<int>* second = split(root);
        if (!second) return root;

        auto* left = mergeSort(root);
        auto* right = mergeSort(second);

        return merge(left, right);
    }

    LinkedListNode<int>* merge(LinkedListNode<int>* left, LinkedListNode<int>* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->val <= right->val) {
            left->next = merge(left->next, right);
            left->next->prev = left;
            return left;
        }
        else {
            right->next = merge(left, right->next);
            right->next->prev = right;
            return right;
        }
    }

    LinkedListNode<int>* split(LinkedListNode<int>* root) {
        if (!root) return root;
        LinkedListNode<int>* second = root->next;

        while (second && second->next) {
            root = root->next;
            second = second->next->next;
        }

        second = root->next;
        root->next = nullptr;

        return second;
    }
};