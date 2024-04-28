#pragma once
#include "../header.h"

class TernarySearchTree {
   private:
    struct Node {
        char val;
        bool isEnd;
        Node *left, *right, *equal;
        Node(char val) : val(val), isEnd(false), left(nullptr), right(nullptr), equal(nullptr) {}
    };
    Node* root = nullptr;

   public:
    static void test() {
        TernarySearchTree obj;
        obj.insert("cat");
        obj.insert("cats");
        obj.insert("up");
        obj.insert("bug");

        obj.print();

        cout << obj.find("cats") << endl;
        cout << obj.find("bu") << endl;
        cout << obj.find("cat") << endl;
    }

   public:
    bool insert(string val) {
        root = insertRecur(root, val, 0);
        return true;
    }

    Node* insertRecur(Node* root, string val, int index) {
        if (!root) root = new Node(val[index]);
        if (index == val.length() - 1) {
            root->isEnd = true;
            return root;
        }

        if (val[index] < root->val) {
            root->left = insertRecur(root->left, val, index);
        } else if (val[index] > root->val) {
            root->right = insertRecur(root->right, val, index);
        } else {
            root->equal = insertRecur(root->equal, val, index + 1);
        }

        return root;
    }

   public:
    bool find(string val) {
        return findRecur(root, val, 0);
    }

    bool findRecur(Node* root, string val, int index) {
        if (!root) return false;
        if (index == val.length() - 1) return root->isEnd;

        if (val[index] < root->val) {
            return findRecur(root->left, val, index);
        } else if (val[index] > root->val) {
            return findRecur(root->right, val, index);
        } else {
            return findRecur(root->equal, val, index + 1);
        }

        return false;
    }

   public:
    void print() {
        vector<string> out;
        printRecur(root, "", out);

        cout << out << endl;
    }

    void printRecur(Node* node, string res, vector<string>& out) {
        if (!node) return;

        if (node->isEnd) {
            out.push_back(res);
            return;
        }

        printRecur(node->left, res, out);

        res += node->val;
        printRecur(node->equal, res, out);
        res.pop_back();

        printRecur(node->right, res, out);
    }

   public:
    void remove(const string& word) {
        root = remove(root, word, 0);
    }

    Node* remove(Node* root, const string& word, int index) {
        if (!root) return nullptr;
        if (index == word.size() - 1) {
            root->isEnd = false;
            if (isLeaf(root)) {
                delete root;
                root = nullptr;
            }

            return root;
        }

        auto ch = word[index];
        if (ch < root->val) {
            root->left = remove(root->left, word, index);
        } else if (ch > root->val) {
            root->right = remove(root->right, word, index);
        } else {
            root->equal = remove(root->equal, word, index + 1);
        }

        if (!root->isEnd && isLeaf(root)) {
            delete root;
            root = nullptr;
        }

        return root;
    }

    bool isLeaf(Node* root) {
        return root->left == nullptr && root->right == nullptr && root->equal == nullptr;
    }
};