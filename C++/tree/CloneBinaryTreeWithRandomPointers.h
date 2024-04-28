#pragma once
#include "../header.h"

class CloneBinaryTreeWithRandomPointers {
    struct Node {
        int val;
        Node *left, *right, *random;
        Node(int val) : val(val), left(nullptr), right(nullptr), random(nullptr) {}
    };

   public:
    Node *cloneTree(Node *orig) {
        unordered_map<Node *, Node *> map;

        Node *clonedNode = cloneLeftRightNodes(orig, map);

        copyRandomPointers(orig, map);
    }

    Node *cloneLeftRightNodes(Node *orig, unordered_map<Node *, Node *> &map) {
        if (!orig) return nullptr;

        map[orig] = new Node(orig->val);

        map[orig]->left = cloneLeftRightNodes(orig->left, map);
        map[orig]->right = cloneLeftRightNodes(orig->right, map);

        return map[orig];
    }

    void copyRandomPointers(Node *orig, unordered_map<Node *, Node *> &map) {
        if (!orig) return;

        map[orig]->random = map[orig->random];
        copyRandomPointers(orig->left, map);
        copyRandomPointers(orig->right, map);
    }
};