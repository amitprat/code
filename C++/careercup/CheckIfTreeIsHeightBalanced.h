#include "../header.h"

class CheckIfTreeIsHeightBalanced {
   public:
   private:
    bool isHeightBalanced(Node *root) {
        int mxHeight = 0;
        return this->isHeightBalanced(root, mxHeight)
    }

    bool isHeightBalanced(Node *root, int &mxHeight) {
        if (!root)
            return true;

        bool ls = isHeightBalanced(root->left, &lh);
        bool rs = isHeightBalanced(root->right, &rh);

        int diff = abs(lh - rh);
        mxHeight = max(lh, rh) + 1;
        if (ls && rs && diff <= 1)
            return true;

        return false;
    }

   private:
    bool isHeightBalanced(Node *root) {
        if (!root)
            return true;

        int lh = this->height(root->left);
        int rh = this->height(root->right);

        if (abs(lh - rh) <= 1 && this->isHeightBalanced(root->left) && this->isHeightBalanced(root->right))
            return true;

        return false;
    }

    int height(Node *root) {
        if (!root)
            return 0;

        return 1 + max(height(root->left), height(root->right));
    }
};