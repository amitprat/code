#include "../header.h"

class CheckIfValidBinarySearchTree {
   private:
    bool isBinarySearchTree(Node *root) {
        return this->isBinarySearchTree(root, INT_MIN, INT_MAX);
    }

    bool isBinarySearchTree(Node *root, int mnValue, int mxValue) {
        if (!root)
            return true;
        if (root->val < mnValue || root->val > mxValue)
            return false;

        return this->isBinarySearchTree(root->left, mnValue, root->val) &&
               this->isBinarySearchTree(root->right, root->val, mxValue);
    }
};