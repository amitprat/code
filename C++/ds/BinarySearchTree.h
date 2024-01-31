#pragma once
#include "../header.h"

template <class K, class V>
class BinarySearchTree {
   public:
    struct Node {
        K key;
        V val;
        Node *left, *right;
        Node(K key, V val) : key(key), val(val), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    BinarySearchTree() {}
    BinarySearchTree(vector<pair<K, V>> vals) {
        for (auto val : vals) {
            root = insert(root, val.first, val.second);
        }
    }

    void insert(K key, V val) {
        root = insert(root, key, val);
    }

    void inorder() {
        cout << "Inorder: ";

        inorder(root);
        cout << endl;
    }

    string to_string() {
        stringstream ss;
        Node* tmp = root;
        to_string(tmp, ss);

        return ss.str();
    }

   private:
    Node* insert(Node* root, K key, V val) {
        if (!root) {
            root = new Node(key, val);
            return root;
        }
        if (key < root->key)
            root->left = insert(root->left, key, val);
        else if (key > root->key)
            root->right = insert(root->right, key, val);
        else
            root->val = val;

        return root;
    }

    void inorder(Node* node) {
        if (!node) return;

        inorder(node->left);
        cout << node->val << " ";
        inorder(node->right);
    }

    void to_string(Node* tmp, stringstream& ss) {
        if (tmp) {
            to_string(tmp->left, ss);
            ss << "{" << tmp->key << ":" << tmp->val << "}";
            ss << ", ";
            to_string(tmp->right, ss);
        }
    }
};