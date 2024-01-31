#pragma once
#include "../header.h"

class FindRankOfElementInBST {
    class BinarySearchTree {
        struct Node {
            int val;
            int size;
            Node *left, *right;

            Node(int val) : val(val), size(1), left(nullptr), right(nullptr) {}
        };

       private:
        Node* root = nullptr;

       public:
        void insert(int val) {
            root = insertInternal(root, val);
        }

        int rank(int elem) {
            return rank(root, elem);
        }

        int rank(Node* cur, int elem) {
            if (cur == nullptr) return 0;

            if (cur->val == elem) return 1 + size(cur->left);
            if (elem < cur->val)
                return rank(cur->left, elem);
            else
                return 1 + size(cur->left) + rank(cur->right, elem);
        }

        int size(Node* cur) {
            if (cur == nullptr) return 0;

            return cur->size;
        }

        string to_string() {
            string res;
            inorder(root, res);
            return res;
        }

       private:
        Node* insertInternal(Node* cur, int val) {
            if (cur == nullptr) return new Node(val);

            cur->size++;
            if (val <= cur->val)
                cur->left = insertInternal(cur->left, val);
            else
                cur->right = insertInternal(cur->right, val);

            return cur;
        }

        void inorder(Node* cur, string& res) {
            if (cur) {
                inorder(cur->left, res);
                res += std::to_string(cur->val) + " ";
                inorder(cur->right, res);
            }
        }
    };

   public:
    static void test() {
        BinarySearchTree tree;
        tree.insert(9);
        tree.insert(7);
        tree.insert(2);
        tree.insert(5);
        tree.insert(8);
        tree.insert(10);

        cout << "Tree:" << tree.to_string() << endl;

        for (int i = 0; i <= 11; i++) {
            cout << "Rank of " << i << ":" << tree.rank(i) << endl;
        }
    }
};