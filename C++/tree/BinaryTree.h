#pragma once
#include "../header.h"

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

    BinaryTree(Node *root) : root(root) {}

   public:
    string preorder() {
        stringstream ss;
        preorder(root, ss);

        return ss.str();
    }

   private:
    void preorder(Node *root, stringstream &ss) {
        if (!root) return;

        ss << root->val << " ";
        preorder(root->left, ss);
        preorder(root->right, ss);
    }

   public:
    list<Node *> preorder_list() {
        list<Node *> out;
        preorder(root, out);

        return out;
    }

    void preorder(Node *root, list<Node *> &out) {
        if (!root) return;

        out.push_back(root);
        preorder(root->left, out);
        preorder(root->right, out);
    }

   public:
    string postorder() {
        stringstream ss;
        postorder(root, ss);

        return ss.str();
    }

   private:
    void postorder(Node *root, stringstream &ss) {
        if (!root) return;

        postorder(root->left, ss);
        postorder(root->right, ss);
        ss << root->val << " ";
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
    string levelOrder() {
        map<int, vector<T>> out;
        levelOrder(out);

        return stringfyMap(out);
    }

   public:
    void levelOrder(map<int, vector<T>> &out) {
        queue<Node *> q;

        if (root) q.push(root);
        int level = 0;
        while (!q.empty()) {
            int sz = q.size();
            out[level] = {};

            while (sz--) {
                auto *cur = q.front();
                q.pop();

                out[level].push_back(cur->val);

                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }

            level++;
        }
    }

   private:
    std::string stringfyMap(const std::map<int, std::vector<T>> &myMap) {
        std::ostringstream oss;

        oss << "{";
        bool firstEntry = true;  // To handle commas correctly
        for (const auto &[key, valueVec] : myMap) {
            if (!firstEntry) oss << ", ";
            firstEntry = false;

            // Key
            oss << key << ": [";

            // Vector values
            for (size_t i = 0; i < valueVec.size(); ++i) {
                oss << valueVec[i];
                if (i != valueVec.size() - 1) oss << ", ";
            }
            oss << "]";
        }
        oss << "}";
        return oss.str();
    }
};