#pragma once
#include "../header.h"
using namespace std;

class MergeTree {
   public:
    class Node {
       public:
        int val;
        Node *left, *right;
        Node(int val, Node* left = nullptr, Node* right = nullptr)
            : val(val), left(left), right(right) {}
    };

   public:
    static void test() {
        MergeTree obj;

        // First tree
        Node* node1 = new Node(10);
        node1->left = new Node(5);
        node1->left->left = new Node(3);
        node1->left->left->right = new Node(4);
        node1->right = new Node(13);
        node1->right->left = new Node(11);
        node1->right->right = new Node(15);
        node1->right->right->right = new Node(17);

        // Second tree
        Node* node2 = new Node(7);
        node2->left = new Node(2);
        node2->right = new Node(9);
        node2->right->left = new Node(8);

        Node* merged = obj.mergeTree(node1, node2);

        cout << "Inorder traversal of merged tree: ";
        obj.inorder(merged);
        cout << endl;
    }

   public:
    Node* mergeTree(Node* node1, Node* node2) {
        if (!node1) return node2;
        if (!node2) return node1;

        Node* newNode = new Node(node1->val + node2->val);
        newNode->left = mergeTree(node1->left, node2->left);
        newNode->right = mergeTree(node1->right, node2->right);

        return newNode;
    }

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
};