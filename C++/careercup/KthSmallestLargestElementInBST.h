#include "../header.h"

class KthSmallestLargestElementInBST {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val) {}
    };

   public:
   private:
    Node *kthSmallestInBst(Node *root, int k) {
        if (!root) return root;

        Node *left = kthSmallestInBst(root->left, k);
        if (left) return left;

        k--;
        if (k == 0) return root;

        return kthSmallestInBst(root->right, k);
    }

   private:
    Node *kthLargestInBST(Node *root, int k) {
        if (!root) return root;

        Node *right = kthLargestInBST(root->right, k);

        k--;
        if (k == 0) return right;

        return kthLargestInBST(root->left, k);
    }
};