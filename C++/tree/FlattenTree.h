#pragma once
#include "../Header.h"

class FlattenTree {
public:
    static void test() {
        ITNode* node = new ITNode(1);
        node->left = new ITNode(2);
        node->right = new ITNode(3);
        node->left->right = new ITNode(4);
        node->right->left = new ITNode(5);

        cout << to_string(node) << endl;

        auto head = flatten(node);

        cout << to_string(head) << endl;
    }

    static ITNode* flatten(ITNode* root) {
        if (!root) return root;

        ITNode* left = flatten(root->left);
        ITNode* next = root->right;

        root->right = left;
        root->left = nullptr;

        ITNode* right = flatten(next);
        getLeaf(root)->right = right;

        return root;
    }

    static ITNode* getLeaf(ITNode* root) {
        while (root && root->right) root = root->right;
        return root;
    }
};