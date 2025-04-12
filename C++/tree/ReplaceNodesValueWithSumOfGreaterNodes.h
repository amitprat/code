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
    void replace_node_values(TreeNode* root) {
        int sum = 0;
        replace_node_values(root, sum);
    }

    void replace_node_values(TreeNode* root, int& sum) {
        if (!root) return;

        replace_node_values(root->right, sum);
        root->val += sum;
        sum = root->val;
        replace_node_values(root->left, sum);
    }
};
