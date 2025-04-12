#pragma once
#include "../header.h"
#include "BinaryTree.h"

/*
Flatten binary tree to linkedlist.

Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
The "linked list" should be in the same order as a pre-order traversal of the binary tree.

https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
*/

class FlattenTree {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->right = new Node(4);
        root->right->left = new Node(5);

        cout << "Tree: " << (new BinaryTree<int>(root))->inorder() << endl;

        auto head = flatten(root);
        cout << "Flattened tree: " << endl;
        printFlattened(head);
    }

   public:
    static Node* flatten(Node* root) {
        if (!root) return root;

        auto right = flatten(root->right);
        auto left = flatten(root->left);

        if (left) {
            getLeaf(left)->right = right;
            root->right = left;
        } else {
            root->right = right;
        }
        root->left = nullptr;

        return root;
    }

    static Node* getLeaf(Node* root) {
        while (root && root->right) root = root->right;
        return root;
    }

   public:
    static void printFlattened(Node* root) {
        const Node* current = root;
        while (current) {
            std::cout << current->val << " ";
            current = current->right;
        }
        std::cout << std::endl;
    }
};