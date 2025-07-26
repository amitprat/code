#pragma once
#include "../header.h"

// Print extreme nodes of each level in alternate order (first leftmost, then rightmost, then leftmost, etc.).
class PrintExtremeNodes {
    using ITNode = BinaryTree<int>::Node;

   public:
    static void test() {
        PrintExtremeNodes obj;

        ITNode* root = new ITNode(10);
        root->left = new ITNode(5);
        root->right = new ITNode(11);
        root->left->left = new ITNode(9);
        root->left->right = new ITNode(20);
        root->right->right = new ITNode(15);
        root->left->left->left = new ITNode(14);
        root->right->right->left = new ITNode(25);
        root->left->left->left->right = new ITNode(30);

        // Tree structure:
        //         10
        //      5      11
        //    9   20      15
        // 14         25
        //    30

        cout << "Extreme nodes in alternate order:" << endl;
        obj.printExtremeNodes(root);
    }

   public:
    void printExtremeNodes(ITNode* root) {
        if (!root) return;

        queue<ITNode*> q;
        q.push(root);
        bool printLeft = true;  // alternate between leftmost and rightmost

        while (!q.empty()) {
            int size = q.size();
            vector<ITNode*> levelNodes;
            levelNodes.reserve(size);

            for (int i = 0; i < size; ++i) {
                ITNode* node = q.front();
                q.pop();
                levelNodes.push_back(node);

                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            if (printLeft)
                cout << "Level extreme (leftmost): " << levelNodes.front()->val << endl;
            else
                cout << "Level extreme (rightmost): " << levelNodes.back()->val << endl;

            printLeft = !printLeft;  // alternate next level
        }
    }
};