#pragma once
#include "../header.h"
#include "../tree/BinaryTree.h"

class MaxPathSumInBinaryTree {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        Node* root = new Node(-15);
        root->left = new Node(10);
        root->right = new Node(20);
        root->right->left = new Node(15);
        root->right->left->left = new Node(-5);
        root->right->right = new Node(5);

        MaxPathSumInBinaryTree obj;
        auto sum = obj.maxPathSum(root);

        println("Max path sum: {}", sum);
    }

   public:
    int maxPathSum(Node* root) {
        int maxSum = INT_MIN;
        maxPathDown(root, maxSum);
        return maxSum;
    }

   private:
    int maxPathDown(Node* node, int& maxSum) {
        if (!node) return 0;

        int left = max(0, maxPathDown(node->left, maxSum));
        int right = max(0, maxPathDown(node->right, maxSum));
        maxSum = max(maxSum, left + right + node->val);

        return node->val + max(left, right);
    }
};