#pragma once
#include "../header.h"

class TreeLevelOrderTraversal {
    static void printLevelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        if (root) q.push(root);

        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto cur = q.front();
                q.pop();

                cout << cur->to_string() << " ";
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << endl;
        }
    }

   public:
    static void test() {
        TreeNode* node = new TreeNode(1);
        node->left = new TreeNode(2);
        node->right = new TreeNode(3);

        printLevelOrder(node);
    }
};