#pragma once
#include "../Header.h"

/*
Sink Zero in Binary Tree. Swap zero value of a node with non-zero value of one of its descendants
so that no node with value zero could be parent of node with non-zero.
*/
class SinkNodesInBinaryTree {
public:
    static void test() {
        SinkNodesInBinaryTree obj;
        ITNode* root = new ITNode(1);
        root->left = new ITNode(0);
        root->right = new ITNode(0);
        root->right->left = new ITNode(0);
        root->right->right = new ITNode(2);
        root->right->left->left = new ITNode(3);
        root->right->left->right = new ITNode(4);

        cout << to_string(root) << endl;

        //root = obj.sinkZeros(root);
        deque<ITNode*> q;
        obj.sinkZeros(root, q);

        cout << to_string(root) << endl;
    }

    void sinkZeros(ITNode* root, deque<ITNode*>& parentQueue) {
        if (!root) return;
        if (root->val == 0) parentQueue.push_back(root);
        else if (!parentQueue.empty()) {
            auto f = parentQueue.front(); parentQueue.pop_front();
            swap(root->val, f->val);
        }

        sinkZeros(root->left, parentQueue);
        sinkZeros(root->right, parentQueue);

        if (!parentQueue.empty()) parentQueue.pop_back();
    }

    ITNode* sinkZeros(ITNode* root) {
        if (!root) return root;

        root->left = sinkZeros(root->left);
        root->right = sinkZeros(root->right);

        if (root->val == 0) {
            sinkDown(root);
        }

        return root;
    }

    void sinkDown(ITNode* root) {
        if (!root) return;
        if (root->val != 0) return;
        if (root->left && root->left->val != 0) {
            swap(root->val, root->left->val);
            sinkDown(root->left);
        }
        else if (root->right && root->right->val != 0) {
            swap(root->val, root->right->val);
            sinkDown(root->right);
        }
    }
};