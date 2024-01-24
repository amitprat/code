#pragma once
#include "../Header.h"

class NearestLeafNode {
public:
    static void test() {
        NearestLeafNode obj;
        ITNode* root = new ITNode(1);
        root->left = new ITNode(2);
        root->right = new ITNode(3);
        root->right->left = new ITNode(31);
        root->right->right = new ITNode(32);
        root->left->left = new ITNode(4);
        root->left->right = new ITNode(5);
        root->left->left->left = new ITNode(6);
        root->left->left->right = new ITNode(7);
        root->left->right->left = new ITNode(8);
        root->left->right->right = new ITNode(9);
        root->left->left->left->left = new ITNode(10);
        root->left->left->left->right = new ITNode(11);
        root->left->left->right->left = new ITNode(12);
        root->left->left->right->right = new ITNode(13);

        int val = obj.findNearestLeaf(root, 1);
        cout << "val = " << val << endl;

        val = obj.findNearestLeaf(root, 2);
        cout << "val = " << val << endl;

        val = obj.findNearestLeaf(root, 3);
        cout << "val = " << val << endl;

        val = obj.findNearestLeaf(root, 4);
        cout << "val = " << val << endl;

        val = obj.findNearestLeaf(root, 5);
        cout << "val = " << val << endl;

        val = obj.findNearestLeaf(root, 6);
        cout << "val = " << val << endl;
    }

    int findNearestLeaf(ITNode* root, int val)
    {
        int mnDistance = INT_MAX;
        nearestLeafNode(root, val, mnDistance);

        return mnDistance;
    }

    pair<int, int> nearestLeafNode(ITNode* root, int val, int& mnDistance) {
        if (!root) return { -1,INT_MAX };

        auto left = nearestLeafNode(root->left, val, mnDistance);
        auto right = nearestLeafNode(root->right, val, mnDistance);

        int mnLeafNodeDist = min(left.first, right.first) + 1;
        int valNodeDist = INT_MAX;
        if (root->val == val) {
            valNodeDist = 0;
        }
        else {
            if (left.second != INT_MAX) {
                valNodeDist = left.second + 1;
            }

            if (right.second != INT_MAX) {
                valNodeDist = right.second + 1;
            }
        }
        mnDistance = min(mnDistance, valNodeDist == INT_MAX ? valNodeDist : mnLeafNodeDist + valNodeDist);

        //cout << "At node " << root->val << ", mnDistance = " << mnDistance << endl;
        //cout << "Return value from node " << root->val << " = " << mnLeafNodeDist << ", " << valNodeDist << endl;

        return { mnLeafNodeDist,valNodeDist };
    }
};