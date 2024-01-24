#include "../header.h"

/*
https://careercup.com/question?id=15645665

Find the k'th largest element in a binary search tree. Write code for


struct Node {
    int val;
    struct Node *left;
    struct Node *right;
} Node;

Node * kth_largest(Node *root, unsigned int k);

Traverse in reverse in-order (i.e. descending order).


Something like this (quick code without thinking, so bugs will be there).


Tree * Largest(Tree *root, const int k) {
    int count = 0;
    return LargestHelper(root, k, count);
}
// Return either NULL (not found), or returns the node.
Tree *LargestHelper(Tree *root, const int k, int &count) {
    if (root == NULL) {
        return NULL;
    }

    Tree *right = LargestHelper(root->right, k, count);

    if (right != NULL) return right;

    count++;
    if (count == k) {
        return root;
    }

    return LargestHelper(root->left, k, count);
}
*/
class KthLargestInBST {
   private:
    int kthLargest(Node* root, int& k) {
        if (!root) return INT_MIN;

        int r = kthLargest(root->right, k);
        if (r != INT_MIN) return r;

        k--;
        if (k == 0) return root->val;
        return kthLargest(root->left, k);
    }
};