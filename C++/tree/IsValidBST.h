#pragma once
#include "../header.h"

class IsValidBST {
    using Node = BinaryTree<int>::Node;

   public:
    bool isValid(Node* root) {
        return isValid(root, INT_MIN, INT_MAX);
    }

    bool isValid(Node* root, int mn, int mx) {
        if (!root) return true;
        if (root->val < mn || root->val > mx) return false;

        return isValid(root->left, mn, root->val - 1) && isValid(root->right, root->val + 1, mx);
    }
};