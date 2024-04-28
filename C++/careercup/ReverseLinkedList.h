#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/reverse-a-linked-list/
*/
class ReverseLinkedList {
    struct Node {
        int val;
        Node *prev, *next;
        Node(int val) : val(val), prev(nullptr), next(nullptr) {}
    };

   public:
    Node *reverseList(Node *head) {
        Node *prev = nullptr;
        while (head) {
            auto next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }

   public:
    Node *reverse_linked_list(Node *orig) {
        Node *root = nullptr;
        reverse(nullptr, orig, &root);
        return root;
    }

    Node *reverse(Node *prev, Node *root, Node **orig) {
        if (root == nullptr) {
            *orig = prev;
            return prev;
        }

        root = reverse(root, root->next, orig);
        root->next = prev;

        return prev;
    }

   public:
    Node *reverseList(Node *root, Node **head) {
        if (!root || !root->next) {
            *head = root;
            return root;
        }

        Node *next = reverseList(root->next, head);
        next->next = root;

        return root;
    }

   public:
    void tailRecur(Node *root, Node *&prev) {
        if (!root) return;
        if (!root->next) {
            root->next = prev;
            prev = root;
            return;
        }

        // head recursion to keep swapping pointers from beginning
        Node *next = root->next;
        root->next = prev;
        prev = root;

        tailRecur(next, prev);
    }

   public:
    void reverseRecursiveUsingRestList(Node *&root) {
        if (!root) return;

        Node *first = root;

        Node *rest = first->next;
        if (!rest) return;

        reverseRecursiveUsingRestList(rest);

        first->next->next = first;
        first->next = nullptr;

        // root always points to last node
        root = rest;
    }
};