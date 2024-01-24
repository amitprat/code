#pragma once
#include "../Header.h"

class PrintUniqueRows {
    class BST {
        struct Node {
            int val;
            bool end = false;
            Node* left, * right, * eq;
            Node() :left(nullptr), right(nullptr), eq(nullptr) {}
            Node(int val) :val(val), left(nullptr), right(nullptr), eq(nullptr) {}
        };

        Node* root = nullptr;
    public:
        void insert(vector<int> row) {
            root = insert(root, row, 0, row.size());
        }

        void traverse() {
            vector<int> out;
            traverse(root, out);
        }

    private:
        Node* insert(Node* node, vector<int>& row, int cur, int sz) {
            if (!node) node = new Node(row[cur]);
            if (cur == sz - 1) {
                node->end = true;
                return node;
            }

            if (row[cur] == node->val) node->eq = insert(node->eq, row, cur + 1, sz);
            else if (row[cur] < node->val) node->left = insert(node->left, row, cur, sz);
            else node->right = insert(node->right, row, cur, sz);

            return node;
        }

        void traverse(Node* node, vector<int> out) {
            if (!node) return;
            if (node->end) {
                cout << out << endl;
                return;
            }

            traverse(node->left, out);

            out.push_back(node->val);
            traverse(node->eq, out);
            out.pop_back();

            traverse(node->right, out);
        }
    };
public:
    static void test() {
        vector<vector<int>> arr = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 1, 0},
            {0, 1, 0, 0, 1},
            {1, 1, 1, 0, 0} };

        BST bst;
        for (auto e : arr) bst.insert(e);

        bst.traverse();
    }
};