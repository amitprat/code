#pragma once
#include "../header.h"

class CheckIfTreeIsHeightBalanced {
    using Node = BinaryTree<int>::Node;

   public:
    bool isHeightBalanced(Node *root) {
        int mxHeight = 0;
        return this->isHeightBalanced(root, mxHeight);
    }

    bool isHeightBalanced(Node *root, int &mxHeight) {
        if (!root) return true;

        int lh = 0, rh = 0;
        bool ls = isHeightBalanced(root->left, lh);
        bool rs = isHeightBalanced(root->right, rh);

        int diff = abs(lh - rh);
        if (ls && rs && diff <= 1) return true;

        return false;
    }

   public:
    bool isHeightBalanced(Node *root) {
        if (!root) return true;

        int lh = this->height(root->left);
        int rh = this->height(root->right);

        if (abs(lh - rh) <= 1 && this->isHeightBalanced(root->left) && this->isHeightBalanced(root->right)) {
            return true;
        }

        return false;
    }

    int height(Node *root) {
        if (!root) return 0;

        return 1 + max(height(root->left), height(root->right));
    }
};