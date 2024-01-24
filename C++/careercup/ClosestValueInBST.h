#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=12697664

Given (i) a non-empty binary search tree with double values (e.g. 3.5) in each node and (ii) a key value K

Write a method to find the closest value to K.
*/
class ClosestValueInBST {
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

        double val = kClosest(root, 3.5);
        cout << val << endl;

        val = kClosest(root, 4.5);
        cout << val << endl;

        val = kClosest(root, 5.5);
        cout << val << endl;

        val = kClosest(root, 2.5);
        cout << val << endl;

        val = kClosest(root, 8);
        cout << val << endl;

        val = kClosest(root, 0.5);
        cout << val << endl;

        val = kClosest(root, 10.5);
        cout << val << endl;
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

        if (curDiff <= leftDiff && curDiff <= rightDiff) return node->val;
        else if (leftDiff <= curDiff && leftDiff <= rightDiff) return left;
        else return right;
    }
};