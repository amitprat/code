#pragma once
#include "../header.h"
#include "TreeNode.h"

class LeastCommonAncestor {
public:
    static void test() {
        LeastCommonAncestor obj;
        TreeNode<int>* tree = new TreeNode<int>(1);
        tree->left = new TreeNode<int>(2);
        tree->left->left = new TreeNode<int>(3);
        tree->left->left->left = new TreeNode<int>(4);
        tree->left->left->left->right = new TreeNode<int>(5);
        tree->right = new TreeNode<int>(6);
        tree->right->left = new TreeNode<int>(7);
        tree->right->left->right = new TreeNode<int>(8);
        tree->right->right = new TreeNode<int>(9);
        auto* node = obj.findLCA(tree, 2, 11);
        if (node == nullptr) cout << "No LCA for " << 2 << ", " << 6 << " exists." << endl;
        else cout << "LCA for " << 2 << ", " << 6 << " is " << node->val << endl;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                auto* node = obj.findLCA(tree, i, j);
                if (node == nullptr) cout << "No LCA for " << i << ", " << j << " exists." << endl;
                else cout << "LCA for " << i << ", " << j << " is " << node->val << endl;
            }
        }
    }

    TreeNode<int>* findLCA(TreeNode<int>* root, int node1, int node2) {
        TreeNode<int>* left = nullptr;
        TreeNode<int>* right = nullptr;
        auto* node = findLCA(root, node1, node2, left, right);
        if (left && right)
            return node;

        return nullptr;
    }

private:
    TreeNode<int>* findLCA(TreeNode<int>* root, int node1, int node2, TreeNode<int>*& node1Node, TreeNode<int>*& node2Node) {
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

        auto* left = findLCA(root->left, node1, node2, node1Node, node2Node);
        auto* right = findLCA(root->right, node1, node2, node1Node, node2Node);

        if (left && right || found) return root;
        return left ? left : right;
    }
};