#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/add-greater-values-every-node-given-bst/
Given a Binary Search Tree (BST), modify it so that all greater values in the given BST are added to every node.
For example, consider the following BST.
              50
           /      \
         30        70
        /   \      /  \
      20    40    60   80

The above tree should be modified to following
              260
           /      \
         330        150
        /   \       /  \
      350   300    210   80

In a BST, I want to replace all nodes with value which is the sum of all the nodes which are greater than equal to the current node.
              5
            2     10

            Output -->
                15
            17     10
*/

class ReplaceNodesValueWithSumOfGivenNodes {
    using TreeNode = BinaryTree<int>::Node;

   public:
    static void test() {
        // Example BST
        TreeNode* root = new TreeNode(5);
        root->left = new TreeNode(3);
        root->right = new TreeNode(8);
        root->left->left = new TreeNode(2);
        root->left->right = new TreeNode(4);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(10);

        cout << "Original inorder: " << (new BinaryTree<int>(root))->inorder() << endl;

        ReplaceNodesValueWithSumOfGivenNodes obj;
        obj.replace_node_values(root);

        cout << "Modified inorder: " << (new BinaryTree<int>(root))->inorder() << endl;
    }

    void replace_node_values(TreeNode* root) {
        int cumulativeSum = 0;
        replace_node_values_helper(root, cumulativeSum);
    }

   private:
    void replace_node_values_helper(TreeNode* root, int& sum) {
        if (!root) return;

        // Traverse right subtree first (greater values)
        replace_node_values_helper(root->right, sum);

        // Update current node value
        root->val += sum;
        sum = root->val;

        // Traverse left subtree
        replace_node_values_helper(root->left, sum);
    }
};
