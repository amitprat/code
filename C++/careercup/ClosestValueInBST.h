#pragma once
#include "../header.h"
#include "../tree/BinaryTree.h"

/*
https://www.careercup.com/question?id=12697664
Given (i) a non-empty binary search tree with double values (e.g. 3.5) in each node and (ii) a key value K
Write a method to find the closest value to K.
*/
class ClosestValueInBST {
    using ITNode = BinaryTree<int>::Node;

   public:
    static void test() {
        ITNode* root = new ITNode(5);
        root->left = new ITNode(3);
        root->left->left = new ITNode(1);
        root->left->right = new ITNode(4);
        root->right = new ITNode(7);
        root->right->left = new ITNode(6);
        root->right->right = new ITNode(8);

        vector<int> res;
        inorder(root, res);
        cout << to_string(res) << endl;

        vector<double> values = {3, 5, 4, 5, 5.5, 2.5, 8, 0.5, 10.5};
        for (auto& val : values) {
            double res = kClosest(root, 3.5);
            println("Closest value to val={0} is res={1}.", val, res);
        }
    }

    static void inorder(ITNode* node, vector<int>& result) {
        if (!node) return;

        inorder(node->left, result);
        result.push_back(node->val);
        inorder(node->right, result);
    }

    static double kClosest(ITNode* node, double val) {
        if (!node) return 0;

        auto left = kClosest(node->left, val);
        auto right = kClosest(node->right, val);

        auto leftDiff = abs(val - left);
        auto rightDiff = abs(val - right);
        auto curDiff = abs(val - node->val);

        if (curDiff <= leftDiff && curDiff <= rightDiff)
            return node->val;
        else if (leftDiff <= curDiff && leftDiff <= rightDiff)
            return left;
        else
            return right;
    }
};