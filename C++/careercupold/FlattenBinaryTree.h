#pragma once
#include "../Header.h"

class FlattenBinaryTree {
public:
    static void test() {
        FlattenBinaryTree obj;
        ITNode* node = new ITNode(1);
        node->left = new ITNode(2);
        node->right = new ITNode(5);
        node->left->left = new ITNode(3);
        node->left->right = new ITNode(4);
        node->right->right = new ITNode(6);

        obj.flatten(node);

        cout << "List: ";
        auto tmp = node;
        while (tmp) {
            cout << tmp->val << " ";
            tmp = tmp->right;
        }
        cout << endl;
    }

    ITNode* flatten(ITNode* node) {
        if (!node) return node;

        ITNode* left = flatten(node->left);
        ITNode* right = flatten(node->right);

        node->left = nullptr;
        node->right = left;
        getRightMostNode(node)->right = right;

        return node;
    }

    ITNode* getRightMostNode(ITNode* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }
};