#pragma once
#include "../Header.h"

class KthLargestElementInBST {
public:
    static void test() {
        KthLargestElementInBST obj;
        ITNode* root = new ITNode(5);
        root->left = new ITNode(3);
        root->left->left = new ITNode(2);
        root->left->left->left = new ITNode(1);
        root->right = new ITNode(8);
        root->right->left = new ITNode(7);
        root->right->right = new ITNode(9);
        root->right->right->right = new ITNode(10);

        cout << to_string(root) << endl;

        int k = 3;
        auto res = obj.kthLargest(root, k);
        cout << "Result = " << res->val << endl;
    }

    ITNode* kthLargest(ITNode* root, int& k) {
        if (!root) return root;
        auto right = kthLargest(root->right, k);
        if (right) return right;
        k--;
        if (k == 0) return root;
        return kthLargest(root->left, k);
    }
};