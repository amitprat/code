#pragma once
#include "../header.h"

class AncestorOfGivenBinaryTree {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        AncestorOfGivenBinaryTree obj;

        Node *root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->right = new Node(4);
        root->right->left = new Node(5);

        for (int i = 1; i <= 10; i++) {
            cout << format("Ancestor of key={0}", i) << endl;
            obj.printAncestors2(root, i);
            cout << endl;
        }
    }

   public:
    bool printAncestors(Node *root, int key) {
        if (!root) return false;

        if (root->val == key) return true;

        auto left = printAncestors(root->left, key);
        if (left) {
            cout << root->val << " ";
        }

        auto right = printAncestors(root->right, key);
        if (right) {
            cout << root->val << " ";
        }

        return left || right;
    }

   public:
    // TODO - correct me
    void printAncestors2(Node *root, int key) {
        stack<Node *> st;
        while (true) {
            while (root && root->val != key) {
                st.push(root);
                root = root->left;
            }

            if (root && root->val == key) {
                break;
            }

            if (!st.empty() && st.top()->right == nullptr) {
                root = st.top();
                st.pop();

                while (!st.empty() && st.top()->right == root) {
                    root = st.top();
                    st.pop();
                }
            }

            root = (!st.empty()) ? st.top()->right : nullptr;
        }

        while (!st.empty()) {
            cout << st.top()->val << " ";
            st.pop();
        }
    }
};