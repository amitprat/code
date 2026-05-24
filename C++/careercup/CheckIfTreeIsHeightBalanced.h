#pragma once
#include "../header.h"

class CheckIfTreeIsHeightBalanced {
    using Node = BinaryTree<int>::Node;

   public:
    bool isHeightBalanced(Node* root) {
        int mxHeight = 0;
        return this->isHeightBalanced(root, mxHeight);
    }

    bool isHeightBalanced(Node* root, int& height) {
        if (!root) {
            height = 0;
            return true;
        }

        int lh = 0, rh = 0;
        bool lb = isHeightBalanced(root->left, lh);
        bool rb = isHeightBalanced(root->right, rh);

        height = max(lh, rh) + 1;

        return lb && rb && abs(lh - rh) <= 1;
    }

   public:
    bool isHeightBalancedBruteForce(Node* root) {
        if (!root) return true;

        int lh = this->height(root->left);
        int rh = this->height(root->right);

        if (abs(lh - rh) <= 1 && this->isHeightBalanced(root->left) && this->isHeightBalanced(root->right)) {
            return true;
        }

        return false;
    }

    int height(Node* root) {
        if (!root) return 0;

        return 1 + max(height(root->left), height(root->right));
    }
};