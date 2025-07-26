#pragma once
#include "../header.h"
#include "BinarySearchTree.h"

class ReconstructTreeFromPreorder {
    using Node = BinarySearchTree<int>::Node;

   public:
    Node* buildBSTFromPreorder(const vector<int>& preorder) {
        int index = 0;
        return build(preorder, index, INT_MIN, INT_MAX);
    }

    Node* build(const vector<int>& preorder, int& index, int minVal, int maxVal) {
        if (index >= preorder.size()) return nullptr;

        int val = preorder[index];
        if (val < minVal || val > maxVal) return nullptr;

        Node* root = new Node(val);
        index++;

        root->left = build(preorder, index, minVal, val);
        root->right = build(preorder, index, val, maxVal);

        return root;
    }

    void printInorder(Node* root) {
        if (!root) return;
        printInorder(root->left);
        cout << root->val << " ";
        printInorder(root->right);
    }

    vector<int> preorder(Node* root) {
        vector<int> arr;
        preorder(root);
    }

    void preorder(Node* root, vector<int>& arr) {
        if (!root) return;
        arr.push_back(root->val);

        preorder(root->left, arr);
        preorder(root->right, arr);
    }

   public:
    static void test() {
        Node* root = new Node(5);
        root->left = new Node(4);
        root->left->left = new Node(1);
        root->left->left->right = new Node(2);
        root->right = new Node(7);
        root->right->left = new Node(6);
        root->right->right = new Node(8);
        root->right->right->right = new Node(9);

        ReconstructTreeFromPreorder obj;

        auto arr = obj.preorder(root);
        cout << "Preorder: " << arr << endl;

        Node* root2 = obj.buildBSTFromPreorder(arr);

        auto arr2 = obj.preorder(root2);
        cout << "Preorder: " << arr2 << endl;
    }
};