#pragma once
#include "../header.h"

class ConnectNodesAtSameLevel {
    struct Node {
        int val;
        Node *left, *right, *nextRight;
        Node(int val) : val(val), left(nullptr), right(nullptr), nextRight(nullptr) {}
    };

   public:
    void connect(Node *root) {
        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int sz = q.size();

            Node *prev = nullptr;
            while (sz--) {
                auto cur = q.front();
                q.pop();

                auto left = cur->left;
                auto right = cur->right;

                if (prev) prev->nextRight = cur;
                prev = cur;

                if (left) q.push(left);
                if (right) q.push(right);
            }
            prev->nextRight = nullptr;
        }
    }

   public:
    // works only for complete tree.
    void connect(Node *p) {
        p->nextRight = nullptr;

        connectRecur(p);
    }

    void connectRecur(Node *p) {
        if (!p) return;

        if (p->left) p->left->nextRight = p->right;
        if (p->right) p->right->nextRight = (p->nextRight) ? p->nextRight->left : nullptr;

        connectRecur(p->left);
        connectRecur(p->right);
    }
};