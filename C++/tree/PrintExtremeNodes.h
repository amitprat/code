#pragma once
#include "../Header.h"

class PrintExtremeNodes {
public:
    static void test() {
        PrintExtremeNodes obj;
        ITNode* root = new ITNode(10);
        root->left = new ITNode(5);
        root->right = new ITNode(11);
        root->left->left = new ITNode(9);
        root->left->right = new ITNode(20);
        root->right->right = new ITNode(15);
        root->left->left->left = new ITNode(14);
        root->right->right->left = new ITNode(25);
        root->left->left->left->right = new ITNode(30);

        cout << to_string(root) << endl;

        unordered_map<int, int> map;
        obj.printExtremeNodes(root, 0, map, true);
        cout << map << endl;
    }

    void printExtremeNodes(ITNode* root, int level, unordered_map<int, int>& map, bool printLeft) {
        if (!root) return;

        if (printLeft) {
            cout << "printLeft" << endl;
            printExtremeNodes(root->right, level + 1, map, !printLeft);
            printExtremeNodes(root->left, level + 1, map, !printLeft);
        }
        else {
            cout << "printRight" << endl;
            printExtremeNodes(root->left, level + 1, map, !printLeft);
            printExtremeNodes(root->right, level + 1, map, !printLeft);
        }

        map[level] = root->val;
    }
};