#pragma once
#include "../header.h"

class TreeLevelOrderTraversal {
    template <class T>
    class TreeNode {
    public:
        T val;
        TreeNode* left, * right;
        TreeNode(T val) : val(val), left(nullptr), right(nullptr) {}

        string to_string() {
            return std::to_string(val);
        }
    };

    template <class T>
    static void printLevelOrder(TreeNode<T>* root) {
        queue<TreeNode<T>*> q;
        if (root) q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto* cur = q.front(); q.pop();
                cout << cur->to_string() << " ";
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << endl;
        }
    }

public:
    static void test() {
        TreeNode<int>* node = new TreeNode<int>(1);
        node->left = new TreeNode<int>(2);
        node->right = new TreeNode<int>(3);

        printLevelOrder(node);
    }
};