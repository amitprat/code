#pragma once
#include "../header.h"

class IsValidBST {
   public:
    bool isValid(TreeNode* root) {
        return isValid(root, INT_MIN, INT_MAX);
    }

    bool isValid(TreeNode* root, int mn, int mx) {
        if (!root) return true;
        if (root->val < mn || root->val > mx) return false;

        return isValid(root->left, mn, root->val - 1) && isValid(root->right, root->val + 1, mx);
    }
};