#pragma once
#include "../header.h"

class KthSmallestElementInBst {
    class Tree {
    public:
        class Node {
        public:
            int val;
            int size;
            Node* left, * right;
            Node(int val) : val(val), size(1), left(nullptr), right(nullptr) {}
            string to_string() {
                return "{" + std::to_string(val) + "," + std::to_string(size) + "}";
            }
        };

    private:
        Node* root = nullptr;
    public:
        void add(int val) {
            root = addInternal(root, val);
        }

        Node* addInternal(Node* node, int val) {
            if (node == nullptr) return new Node(val);

            node->size++;
            if (val < node->val) {
                node->left = addInternal(node->left, val);
            }
            else {
                node->right = addInternal(node->right, val);
            }

            return node;
        }

        string to_string() {
            vector<string> res;
            to_string_internal(root, res);

            return ::to_string(res);
        }

        int findKthSmallestElement(int k) {
            auto res1 = findKthSmallestElementInternal(root, k);
            int cnt = 0;
            auto res2 = findKthSmallestElementInternal(root, k);
            auto res3 = findKthSmallestElementInternal3(root, k);

            assert(res1 == res2);
            assert(res1 == res3);

            return res1;
        }

    private:
        int findKthSmallestElementInternal(Node* node, int k, int& cnt) {
            if (node == nullptr) return -1;

            int left = findKthSmallestElementInternal(node->left, k, cnt);
            if (left != -1) return left;

            cnt++;
            if (cnt == k) {
                return node->val;
            }

            return findKthSmallestElementInternal(node->right, k, cnt);
        }

        int findKthSmallestElementInternal(Node* node, int k) {
            if (node == nullptr) return -1;

            if (node->left != nullptr) {
                if (node->left->size + 1 == k) return node->val;
                if (k <= node->left->size) return findKthSmallestElementInternal(node->left, k);
                else return findKthSmallestElementInternal(node->right, k - 1 - node->left->size);
            }
            else {
                if (k == 1) return node->val;
                return findKthSmallestElementInternal(node->right, k - 1);
            }
        }

        int findKthSmallestElementInternal3(Node* node, int k) {
            if (node == nullptr) return -1;

            int curSize = size(node->left) + 1;
            if (curSize == k) return node->val;
            else if (k < curSize) return findKthSmallestElementInternal3(node->left, k);
            else return findKthSmallestElementInternal3(node->right, k - curSize);
        }

        void to_string_internal(Node* node, vector<string>& res) {
            if (node != nullptr) {
                to_string_internal(node->left, res);
                res.push_back(node->to_string());
                to_string_internal(node->right, res);
            }
        }

        int size(Node* root) {
            return root ? root->size : 0;
        }
    };

public:
    static void test() {
        Tree tree;
        tree.add(3);
        tree.add(4);
        tree.add(1);
        tree.add(2);

        cout << tree.to_string() << endl;

        int k = 0;
        cout << "Kth smallest element = " << tree.findKthSmallestElement(k) << endl;

        k = 1;
        cout << "Kth smallest element = " << tree.findKthSmallestElement(k) << endl;

        k = 2;
        cout << "Kth smallest element = " << tree.findKthSmallestElement(k) << endl;

        k = 3;
        cout << "Kth smallest element = " << tree.findKthSmallestElement(k) << endl;

        k = 4;
        cout << "Kth smallest element = " << tree.findKthSmallestElement(k) << endl;

        k = 5;
        cout << "Kth smallest element = " << tree.findKthSmallestElement(k) << endl;
    }
};