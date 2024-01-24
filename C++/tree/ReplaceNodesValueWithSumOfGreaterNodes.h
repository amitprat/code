#pragma once
#include "../Header.h"

/*
In a BST, I want to replace all nodes with value which is the sum of all the nodes which are greater than equal to the current node.
5
2 10

Output -->
15
17 10
*/

int sum = 0;
void changeTree(ITNode* root) {
    if (root != nullptr) {
        changeTree(root->right);
        root->val += sum;
        sum = root->val;
        changeTree(root->left);
    }
}