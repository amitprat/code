#pragma once
#include "../header.h"
#include "TreeNode.h"

class CopyTree {
public:
    static void test() {
        CopyTree obj;
        TreeNode<int>* root1 = new TreeNode<int>(1);
        root1->left = new TreeNode<int>(2);
        root1->left->left = new TreeNode<int>(3);
        root1->left->left->right = new TreeNode<int>(4);
        root1->right = new TreeNode<int>(5);
        root1->right->left = new TreeNode<int>(6);
        root1->right->right = new TreeNode<int>(7);

        cout << "Original tree:" << endl;
        printLevelOrder(root1);

        TreeNode<int>* root2 = obj.copyTree(root1);
        cout << "Original tree (after copy):" << endl;
        printLevelOrder(root1);
        cout << "New tree (after copy):" << endl;
        printLevelOrder(root2);

        root1 = obj.deleteTree(root1);

        cout << "Original tree (after delete):" << endl;
        printLevelOrder(root1);
        cout << "New tree (after delete):" << endl;
        printLevelOrder(root2);
    }

    TreeNode<int>* copyTree(TreeNode<int>* root) {
        if (!root) return nullptr;
        TreeNode<int>* newRoot = new TreeNode<int>(root->val);
        newRoot->left = copyTree(root->left);
        newRoot->right = copyTree(root->right);

        return newRoot;
    }

    TreeNode<int>* deleteTree(TreeNode<int>* root) {
        if (!root) return nullptr;
        root->left = deleteTree(root->left);
        root->right = deleteTree(root->right);
        delete root;
        root = nullptr;
        return root;
    }
};