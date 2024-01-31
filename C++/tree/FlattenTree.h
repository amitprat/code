#pragma once
#include "../header.h"
#include "Tree.h"

class FlattenTree {
    using Node = Tree<int>::Node;

   public:
    static void test() {
        Node* node = new Node(1);
        node->left = new Node(2);
        node->right = new Node(3);
        node->left->right = new Node(4);
        node->right->left = new Node(5);

        Tree<int> tree;
        tree.root = node;

        cout << "Tree: " << tree.inorder() << endl;

        auto head = flatten(node);
        Tree<int> tree2;
        tree2.root = head;
        cout << "Flattened Tree: " << tree2.inorder() << endl;
    }

   public:
    static Node* flatten(Node* root) {
        if (!root) return root;

        Node* left = flatten(root->left);
        Node* next = root->right;

        root->right = left;
        root->left = nullptr;

        Node* right = flatten(next);
        getLeaf(root)->right = right;

        return root;
    }

    static Node* getLeaf(Node* root) {
        while (root && root->right) root = root->right;
        return root;
    }
};