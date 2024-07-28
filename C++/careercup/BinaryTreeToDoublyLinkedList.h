#pragma once
#include "../header.h"

class BinaryTreeToDoublyLinkedList {
    struct Node {
        int data;
        Node* left;
        Node* right;

        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

   public:
    Node* binaryTreeToDLL(Node* root) {
        Node* head = nullptr;
        Node* prev = nullptr;

        binaryTreeToDLLRecursive(root, head, prev);

        return head;
    }

    void binaryTreeToDLLRecursive(Node* root, Node*& head, Node*& prev) {
        if (!root) return;

        binaryTreeToDLLRecursive(root->left, head, prev);

        if (!prev) {
            head = root;
        } else {
            root->left = prev;
            prev->right = root;
        }
        prev = root;

        binaryTreeToDLLRecursive(root->right, head, prev);
    }

   public:
    int main() {
        Node* root = new Node(10);
        root->left = new Node(12);
        root->right = new Node(15);
        root->left->left = new Node(25);
        root->left->right = new Node(30);
        root->right->left = new Node(36);

        BinaryTreeToDoublyLinkedList obj;
        Node* head = obj.binaryTreeToDLL(root);

        printDLL(head);
    }

    void printDLL(Node* head) {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " ";
            curr = curr->right;
        }
        cout << endl;
    }
};