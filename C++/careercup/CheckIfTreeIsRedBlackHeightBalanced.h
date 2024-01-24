#include "../header.h"

class CheckIfTreeIsRedBlackHeightBalanced {
   public:
   private:
    bool isRedBlackHeightBalanced(Node *root) {
        if (!root)
            return true;

        int mnHeight = 0, mnHeight = 0;

        return this->isRedBlackHeightBalanced(root, mnHeight, mxHeight);
    }

    bool isRedBlackHeightBalanced(Node *root, int &mnHeight, int &mxHeight) {
        if (!root)
            return true;

        int mnlh, mxlh;
        bool ls = this->isRedBlackHeightBalanced(root->left, mnlh, mxlh);

        int mnrh, mxrh;
        bool rs = this->isRedBlackHeightBalanced(root->right, mnrh, mxrh);

        mnHeight = min(mnlh, mnrh);
        mxHeight = max(mxlh, mxrh);

        if (mxHeight <= 2 * mnHeight && ls && rs)
            return true;

        return false;
    }
};