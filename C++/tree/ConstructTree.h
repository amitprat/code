#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=2478

Given a preorder and inorder traversal of a binary tree, can you reproduce the tree?
if yes, then write a function using C/C++ that builds the tree and returns the root node of the tree.
*/

class ConstructTree {
    using TreeNode = BinaryTree<int>::Node;

   public:
    static void test() {
        ConstructTree obj;

        TreeNode* root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->left = new TreeNode(4);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);

        vector<int> preorder, inorder;
        obj.getPreorder(root, preorder);
        obj.getInorder(root, inorder);

        println("Preorder: {0}", preorder);
        println("Inorder: {0}", inorder);

        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }

        TreeNode* newTree = obj.constructTree(preorder, inorder, 0, inorder.size() - 1, map);

        preorder.clear();
        inorder.clear();
        obj.getPreorder(newTree, preorder);
        obj.getInorder(newTree, inorder);

        println("Preorder: {0}", preorder);
        println("Inorder: {0}", inorder);
    }

   private:
    TreeNode* constructTree(vector<int>& preorder, vector<int>& inorder, int l, int r, unordered_map<int, int>& map) {
        if (l > r) return nullptr;

        static int index = 0;
        TreeNode* root = new TreeNode(preorder[index++]);
        if (l == r) return root;

        int pos = map[root->val];

        root->left = constructTree(preorder, inorder, l, pos - 1, map);
        root->right = constructTree(preorder, inorder, pos + 1, r, map);

        return root;
    }

   private:
    void getPreorder(TreeNode* root, vector<int>& order) {
        if (!root) return;

        order.push_back(root->val);

        getPreorder(root->left, order);
        getPreorder(root->right, order);
    }

    void getInorder(TreeNode* root, vector<int>& order) {
        if (!root) return;

        getInorder(root->left, order);
        order.push_back(root->val);
        getInorder(root->right, order);
    }
};