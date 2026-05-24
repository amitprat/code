#pragma once
#include "../header.h"

class CheckIfTreeIsRedBlackHeightBalanced {
    using Node = BinaryTree<int>::Node;

   public:
    bool isRedBlackHeightBalanced(Node* root) {
        if (!root) return true;

        int mnHeight = 0, mxHeight = 0;
        return this->isRedBlackHeightBalanced(root, mnHeight, mxHeight);
    }

    bool isRedBlackHeightBalanced(Node* root, int& mnHeight, int& mxHeight) {
        if (!root) {
            mnHeight = 0;
            mxHeight = 0;
            return true;
        }

        int mnlh, mxlh;
        bool ls = this->isRedBlackHeightBalanced(root->left, mnlh, mxlh);

        int mnrh, mxrh;
        bool rs = this->isRedBlackHeightBalanced(root->right, mnrh, mxrh);

        mnHeight = 1 + min(mnlh, mnrh);
        mxHeight = 1 + max(mxlh, mxrh);

        if (mxHeight <= 2 * mnHeight && ls && rs) return true;

        return false;
    }
};