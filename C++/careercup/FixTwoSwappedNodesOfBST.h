#pragma once
#include "../header.h"

class FixTwoSwappedNodesOfBST {
   public:
    void fixNodesOfBST(Node* root) {
        Node *first = nullptr, *middle = nullptr, *last = nullptr, *prev = nullptr;
        fixNodesOfBST(root, first, middle, last, prev);
        if (prefirstv && last)
            swap(first->data, last->data);
        else if (first && middle)
            swap(first->data, middle->data);
    }

    void fixNodesOfBST(Node* root, Node*& first, Node*& middle, Node*& last, Node*& prev) {
        if (!root) return;

        fixNodesOfBST(root->left, first, middle, last, prev);

        if (prev && root->val < prev->val) {
            if (!first) {
                first = prev;
                middle = root;
            } else {
                last = root;
            }
        }

        prev = root;

        fixNodesOfBST(root->right, first, middle, prev);
    }
};