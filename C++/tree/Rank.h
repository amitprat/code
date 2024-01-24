#pragma once
#include "../header.h"

class BstNode {
public:
    int val;
    int size;
    BstNode* left, * right;

    BstNode(int val) : val(val), size(1), left(nullptr), right(nullptr) {}
};

class Bst {
private:
    BstNode* root = nullptr;
public:
    void insert(int val) {
        root = insertInternal(root, val);
    }

    int rank(int elem) {
        return rank(root, elem);
    }

    int rank_missingelement(int elem) {
        return rank_missingelement(root, elem);
    }

    string to_string() {
        string res;
        inorder(root, res);
        return res;
    }

private:
    BstNode* insertInternal(BstNode* cur, int val) {
        if (cur == nullptr) return new BstNode(val);

        cur->size++;
        if (val <= cur->val) cur->left = insertInternal(cur->left, val);
        else cur->right = insertInternal(cur->right, val);

        return cur;
    }

    int rank(BstNode* cur, int elem) {
        if (cur == nullptr) return -1;
        if (cur->val == elem) return size(cur->left);
        if (elem < cur->val) return rank(cur->left, elem);
        else {
            int right = rank(cur->right, elem);
            if (right == -1) return right;
            return 1 + size(cur->left) + right;
        }
    }

    int rank_missingelement(BstNode* cur, int elem) {
        if (cur == nullptr) return 0;
        if (cur->val == elem) return size(cur->left);
        if (elem < cur->val) return rank_missingelement(cur->left, elem);
        else return 1 + size(cur->left) + rank_missingelement(cur->right, elem);
    }

    int size(BstNode* cur) {
        if (cur == nullptr) return 0;
        return cur->size;
    }

    void inorder(BstNode* cur, string& res) {
        if (cur) {
            inorder(cur->left, res);
            res += std::to_string(cur->val) + " ";
            inorder(cur->right, res);
        }
    }
};

class Rank {
public:
    static void test() {
        Bst tree;
        tree.insert(9);
        tree.insert(7);
        tree.insert(2);
        tree.insert(5);
        tree.insert(8);
        tree.insert(10);

        cout << "Tree:" << tree.to_string() << endl;

        for (int i = 0; i <= 11; i++) {
            cout << "Rank of " << i << ":" << tree.rank_missingelement(i) << endl;
        }
    }
};