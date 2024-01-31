#pragma once
#include "../header.h"
#include "Tree.h"

class CopyTree {
    using Node = Tree<int>::Node;

   public:
    static void test() {
        CopyTree obj;

        Tree<int> tree;
        tree.root = new Node(1);
        tree.root->left = new Node(2);
        tree.root->left->left = new Node(3);
        tree.root->left->left->right = new Node(4);
        tree.root->right = new Node(5);
        tree.root->right->left = new Node(6);
        tree.root->right->right = new Node(7);

        cout << "Original tree:" << endl;
        tree.printLevelOrder();

        Tree<int> tree2;
        tree2.root = obj.copyTree(tree.root);
        cout << "Original tree (after copy):" << endl;
        tree.printLevelOrder();

        cout << "New tree (after copy):" << endl;
        tree2.printLevelOrder();

        Tree<int> tree3;
        tree3.root = obj.deleteTree(tree2.root);

        cout << "Original tree (after delete):" << endl;
        tree.printLevelOrder();

        cout << "New tree (after delete):" << endl;
        tree3.printLevelOrder();
    }

   public:
    Node* copyTree(Node* root) {
        if (!root) return nullptr;

        Node* newRoot = new Node(root->val);
        newRoot->left = copyTree(root->left);
        newRoot->right = copyTree(root->right);

        return newRoot;
    }

    Node* deleteTree(Node* root) {
        if (!root) return nullptr;

        root->left = deleteTree(root->left);
        root->right = deleteTree(root->right);

        delete root;
        root = nullptr;

        return root;
    }
};