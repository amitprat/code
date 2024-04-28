#pragma once
#include "../header.h"

class FloorAndCeilOfBst {
    using Node = BinaryTree<int>::Node;

   public:
    Node *ceil(Node *root, int key) {
        if (!root) return nullptr;

        if (root->val == key) return root;

        if (key > root->val) return ceil(root->right, key);

        auto val = ceil(root->left, key);
        if (val) return val;

        return root;
    }

   public:
    Node *floor(Node *root, int key) {
        if (!root) return nullptr;

        if (root->val == key) return root;

        if (key < root->val) return floor(root->left, key);

        auto val = floor(root->right, key);
        if (val) return val;

        return root;
    }

   public:
    void floorAndCeil(Node *root, int key, Node *&floor, Node *&ceil) {
        if (!root) return;

        if (root->val == key) {
            floor = ceil = root;
            return;
        }

        if (key < root->val) {
            ceil = root;
            floorAndCeil(root->left, key, floor, ceil);
        } else {
            floor = root;
            floorAndCeil(root->right, key, floor, ceil);
        }
    }
};