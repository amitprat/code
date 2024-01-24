#pragma once
#include "../header.h"

class KthSmallestElementBST {
private:
    template <class T>
    class Tree {
    public:
        class Node {
        public:
            T val;
            Node* left, * right;
            int sz = 0;
            Node(T val) :val(val), left(nullptr), right(nullptr), sz(1) {}
        };
    private:
        Node* root = nullptr;
    public:
        void insert(T item) {
            if (root == nullptr) root = new Node(item);
            else root = insert(root, item);
        }
        Node* getRoot() {
            return root;
        }

    private:
        Node* insert(Node* cur, T item) {
            if (cur == nullptr) return new Node(item);

            if (item < cur->val) {
                cur->sz++;
                cur->left = insert(cur->left, item);
            }
            else if (item > cur->val) {
                cur->sz++;
                cur->right = insert(cur->right, item);
            }
            else cur->val = item;

            return cur;
        }
    };
public:
    static void test() {
        KthSmallestElementBST obj;
        Tree<int> tree;
        tree.insert(1);
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        tree.insert(2);

        for (int k = 1; k <= 5; k++) {
            auto tmp = k;
            cout << k << "th smallest element = " << obj.getKthSmallestIter(tree.getRoot(), tmp) << endl;
        }
    }

    int getKthSmallest(Tree<int>::Node* root, int& k) {
        if (root == nullptr) return INT_MIN;

        auto left = getKthSmallest(root->left, k);
        if (left != INT_MIN) return left;

        k--;
        if (k == 0) return root->val;

        return getKthSmallest(root->right, k);
    }

    int getKthSmallestOrder(Tree<int>::Node* root, int k) {
        if (root == nullptr) return INT_MIN;

        int cur = size(root->left) + 1;
        if (cur == k) return root->val;

        if (k < cur) return getKthSmallestOrder(root->left, k);
        return getKthSmallestOrder(root->right, k - cur);
    }

    int getKthSmallestIter(Tree<int>::Node* root, int k) {
        stack< Tree<int>::Node*> st;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            root = st.top(); st.pop();
            
            k--;
            if (k == 0) return root->val;
            
            root = root->right;
        }
        return -1;
    }

    int size(Tree<int>::Node* root) {
        if (root == nullptr) return 0;
        return root->sz;
    }
};