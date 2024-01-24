#pragma once
#include "../Header.h"

class GoogleProblems {
    struct Node {
        int val;
        Node* left, * right;
        int size = 1;
        Node(int val, Node* left = nullptr, Node* right = nullptr) :val(val), left(nullptr), right(nullptr) {}
    };
    static Node* insert(Node* root, int val) {
        if (!root) return new Node(val);
        if (val < root->val) root->left = insert(root->left, val);
        else root->right = insert(root->right, val);
        root->size++;

        return root;
    }
public:
    static void numberOfNodesHavingValueInRange() {
        Node* root = nullptr;
        root = insert(root, 5);
        root = insert(root, 3);
        root = insert(root, 7);
        root = insert(root, 1);
        root = insert(root, 4);
        root = insert(root, 6);
        root = insert(root, 8);

        for (int l = 0; l <= 10; l++) {
            for (int r = l; r <= 10; r++) {
                int right = countNodes(root, r);
                int left = countNodes(root, l - 1);
                int cnt = right - left;

                int less = countNodes(root, { l,r }, true);
                int greater = countNodes(root, { l,r }, false);
                int cnt2 = root->size - less - greater;

                assert(cnt == cnt2);
                cout << format("l={},r={} count = {}", l, r, cnt) << endl;
            }
            cout << endl;
        }
    }

private:
    static int countNodes(Node* root, int value) {
        if (!root) return 0;

        if (root->val <= value) return 1 + size(root->left) + countNodes(root->right, value);
        else return countNodes(root->left, value);
    }

    static int countNodes(Node* root, pair<int, int> range, bool less) {
        if (!root) return 0;
        if (less) {
            if (root->val <= range.first) return (root->val < range.first) + size(root->left) + countNodes(root->right, range, less);
            else return countNodes(root->left, range, less);
        }
        else {
            if (root->val >= range.second) return (root->val > range.second) + size(root->right) + countNodes(root->left, range, less);
            else return countNodes(root->right, range, less);
        }

        return 0;
    }

    static int size(Node* root) {
        if (!root) return 0;
        return root->size;
    }
};