#pragma once
#include "../Header.h"

class PopulateNextRight {
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Node* nextRight = nullptr;
        int val;
        Node(int val) :val(val) {}
    };
public:
    static void test() {
        PopulateNextRight obj;
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);
        root->left->right = new Node(5);
        root->left->left->left = new Node(8);
        root->left->left->right = new Node(9);
        root->right->left = new Node(6);
        root->right->right = new Node(7);
        root->right->right->left = new Node(10);
        root->right->right->right = new Node(11);

        obj.populateNextRight(root);

        int mxLevel = -1;
        obj.print(root, 0, mxLevel);
    }

    void print(Node* root, int level, int& mxLevel) {
        if (!root) return;

        if (level > mxLevel) {
            printList(root);
            mxLevel = level;
        }

        print(root->left, level + 1, mxLevel);
        print(root->right, level + 1, mxLevel);
    }

    void printList(Node* root) {
        while (root) {
            cout << root->val << " ";
            root = root->nextRight;
        }
        cout << endl;
    }

    void populateNextRight(Node*& root) {
        if (!root) return;

        populateNextRight(root->right);
        auto* nextRight = getNextRight(root);
        if (root->right) {
            root->right->nextRight = nextRight;
        }
        if (root->left) {
            root->left->nextRight = root->right ? root->right : nextRight;
        }
        populateNextRight(root->left);
    }

    Node* getNextRight(Node* root) {
        while (root->nextRight) {
            root = root->nextRight;
            if (root->left) return root->left;
            if (root->right) return root->right;
        }
        return nullptr;
    }
};