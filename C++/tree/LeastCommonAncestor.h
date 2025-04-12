#pragma once
#include "../header.h"
#include "BinaryTree.h"

class LeastCommonAncestor {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        LeastCommonAncestor obj;
        Node* root = new Node(1);
        root->left = new Node(2);
        root->left->left = new Node(3);
        root->left->left->left = new Node(4);
        root->left->left->left->right = new Node(5);
        root->right = new Node(6);
        root->right->left = new Node(7);
        root->right->left->right = new Node(8);
        root->right->right = new Node(9);

        auto* node = obj.findLCA(root, 2, 11);
        if (node == nullptr)
            cout << "No LCA for " << 2 << ", " << 6 << " exists." << endl;
        else
            cout << "LCA for " << 2 << ", " << 6 << " is " << node->val << endl;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                auto* node = obj.findLCA(root, i, j);
                if (node == nullptr)
                    cout << "No LCA for " << i << ", " << j << " exists." << endl;
                else
                    cout << "LCA for " << i << ", " << j << " is " << node->val << endl;
            }
        }
    }

   public:
    Node* findLCA(Node* root, int node1, int node2) {
        Node* left = nullptr;
        Node* right = nullptr;

        auto* node = findLCA(root, node1, node2, left, right);
        if (left && right)
            return node;

        return nullptr;
    }

   private:
    Node* findLCA(Node* root, int node1, int node2, Node*& node1Node, Node*& node2Node) {
        if (root == nullptr) return root;

        bool found = false;
        if (root->val == node1) {
            node1Node = root;
            found = true;
        }
        if (root->val == node2) {
            node2Node = root;
            found = true;
        }

        if (found) return root;

        auto* left = findLCA(root->left, node1, node2, node1Node, node2Node);
        auto* right = findLCA(root->right, node1, node2, node1Node, node2Node);

        return left ? left : right;
    }

   public:
    Node* findLCA2(Node* root, int node1, int node2) {
        auto lca = findLCA2Internal(root, node1, node2);

        return lca && exists(root, node1) && exists(root, node2) ? lca : nullptr;
    }

    Node* findLCA2Internal(Node* root, int node1, int node2) {
        if (!root) return nullptr;

        if (root->val == node1 || root->val == node2) return root;

        auto left = findLCA2Internal(root->left, node1, node2);
        auto right = findLCA2Internal(root->right, node1, node2);

        return left ? left : right;
    }

    bool exists(Node* root, int val) {
        if (!root) return false;

        if (root->val == val) return true;

        return exists(root->left, val) || exists(root->right, val);
    }
};