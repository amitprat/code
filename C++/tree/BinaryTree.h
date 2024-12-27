#pragma once
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class BinaryTree {
   public:
    class Node {
       public:
        T val;
        int sz;

        Node *left, *right;

        Node(T val) : val(val), sz(0), left(nullptr), right(nullptr) {}

        string to_string() {
            return std::to_string(val);
        }
    };

   public:
    Node *root = nullptr;

   public:
    string inorder() {
        stringstream ss;
        inorder(root, ss);

        return ss.str();
    }

   private:
    void inorder(Node *root, stringstream &ss) {
        if (!root) return;

        inorder(root->left);
        ss << root->val << " ";
        inorder(root->right);
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