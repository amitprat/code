#pragma once
#include "../header.h"
#include "BinarySearchTree.h"

/*
Given a Binary Tree (BT), convert it to a Doubly Linked List(DLL) In-Place.
The left and right pointers in nodes are to be used as previous and next pointers respectively in converted DLL.
The order of nodes in DLL must be same as Inorder of the given Binary Tree.
The first node of Inorder traversal (leftmost node in BT) must be the head node of the DLL.

https://www.careercup.com/question?id=6070872
https://leetcode.com/discuss/interview-question/4177029/Binary-Tree-to-DLL/
https://www.geeksforgeeks.org/convert-binary-tree-to-doubly-linked-list-using-inorder-traversal/
*/

class BinarySearchTreeToDoublyLinkedList {
   public:
    static void test() {
        BinarySearchTreeToDoublyLinkedList obj;

        BinarySearchTree<int> bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(20);
        bst.insert(30);
        cout << "Binary search tree inorder: " << bst.inorder() << endl;

        BinarySearchTree<int>::Node* head = nullptr;
        obj.covertBSTToDLL(bst.root, head);

        cout << "Converted dll: ";
        while (head) {
            cout << head->val << " ";
            head = head->right;
        }

        cout << endl;
    }

   private:
    void covertBSTToDLL(BinarySearchTree<int>::Node* root, BinarySearchTree<int>::Node*& head) {
        if (!root) return;

        static BinarySearchTree<int>::Node* prev = nullptr;
        covertBSTToDLL(root->left, head);
        if (!prev)
            head = root;
        else
            prev->right = root;
        root->left = prev;
        prev = root;
        covertBSTToDLL(root->right, head);
    }

   private:
    BinarySearchTree<int>::Node* covertBSTToDLL2(BinarySearchTree<int>::Node* root) {
        BinarySearchTree<int>::Node* next = nullptr;
        return covertBSTToDLL2(root, next);
    }

    BinarySearchTree<int>::Node* covertBSTToDLL2(BinarySearchTree<int>::Node* root, BinarySearchTree<int>::Node*& next) {
        if (!root) return root;

        covertBSTToDLL(root->right, next);

        root->right = next;
        if (next) next->left = root;
        next = root;

        covertBSTToDLL(root->left, next);

        return next;
    }
};