#pragma once
#include "../header.h"

template <class T>
class BinarySearchTree {
   public:
    class Node {
       public:
        T val;
        Node *left, *right;

        Node(T val) : val(val), left(nullptr), right(nullptr) {}

        string to_string() {
            return std::to_string(val);
        }
    };

   public:
    Node *root = nullptr;

   public:
    void insert(T val) {
        root = insert(root, val);
    }

   private:
    Node *insert(Node *root, T val) {
        if (!root) return new Node(val);

        if (val < root->val) {
            root->left = insert(root->left, val);
        } else if (val > root->val) {
            root->right = insert(root->right, val);
        } else {
            root->val = val;
        }

        return root;
    }

   public:
    string inorder() {
        stringstream ss;
        inorder(root, ss);

        return ss.str();
    }

   private:
    void inorder(Node *root, stringstream &ss) {
        if (!root) return;

        inorder(root->left, ss);
        ss << root->val << " ";
        inorder(root->right, ss);
    }

   public:
    void printLevelOrder() {
        queue<Node *> q;

        if (root) q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            cout << "Level " << level++ << " : ";
            while (sz--) {
                auto *cur = q.front();
                q.pop();
                cout << cur->to_string() << " ";

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << endl;
        }
    }
};