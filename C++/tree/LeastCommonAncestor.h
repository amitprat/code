#pragma once
#include <iostream>

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

        std::cout << "=== Testing LCA ===" << std::endl;

        std::pair<int, int> pairs[] = {
            {2, 11}, {2, 6}, {3, 5}, {4, 9}, {7, 8}, {5, 8}, {9, 11}, {3, 4}, {3, 10}, {10, 11}};

        for (auto [a, b] : pairs) {
            auto* node = obj.findLCA(root, a, b);
            if (node == nullptr)
                std::cout << "No LCA for " << a << ", " << b << " exists." << std::endl;
            else
                std::cout << "LCA for " << a << ", " << b << " is " << node->val << std::endl;
        }
    }

   public:
    // ----------------------------------------------------------
    // Public entry point
    // ----------------------------------------------------------
    Node* findLCA(Node* root, int node1, int node2) {
        bool found1 = false, found2 = false;
        Node* lca = findLCAInternal(root, node1, node2, found1, found2);

        // Only return LCA if both nodes were found
        return (found1 && found2) ? lca : nullptr;
    }

   private:
    // ----------------------------------------------------------
    // Recursive helper returns LCA if both found in subtree
    // ----------------------------------------------------------
    Node* findLCAInternal(Node* root, int node1, int node2,
                          bool& found1, bool& found2) {
        if (!root) return nullptr;

        Node* left = findLCAInternal(root->left, node1, node2, found1, found2);
        Node* right = findLCAInternal(root->right, node1, node2, found1, found2);

        if (root->val == node1) {
            found1 = true;
            return root;
        }
        if (root->val == node2) {
            found2 = true;
            return root;
        }

        if (left && right) return root;  // both found in different subtrees
        return left ? left : right;
    }

   public:
    // Returns faster even if single value exists
    Node* findLCA2(Node* root, int node1, int node2) {
        if (!root) return nullptr;
        if (root->val == node1 || root->val == node2) return root;

        auto left = findLCA2(root->left, node1, node2);
        auto right = findLCA2(root->right, node1, node2);

        return left ? left : right;
    }
};