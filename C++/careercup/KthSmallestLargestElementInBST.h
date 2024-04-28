#pragma once
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
        if(right) return right;

        k--;
        if (k == 0) return right;

        return kthLargestInBST(root->left, k);
    }
};