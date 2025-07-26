#pragma once
#include <climits>
#include <sstream>
#include <vector>

#include "../header.h"
#include "BinaryTree.h"
using namespace std;

class SerializeDeserializeBST {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        SerializeDeserializeBST obj;

        Node* root = new Node(3);
        root->left = new Node(1);
        root->right = new Node(5);
        root->left->right = new Node(2);
        root->right->left = new Node(4);

        cout << "Original inorder: " << (new BinaryTree<int>(root))->inorder() << endl;

        string serialized = obj.serialize(root);
        cout << "Serialized: " << serialized << endl;

        Node* deserialized = obj.deserialize(serialized);
        cout << "Deserialized inorder: " << (new BinaryTree<int>(deserialized))->inorder() << endl;
    }

   public:
    // Preorder serialization
    string serialize(Node* node) {
        if (!node) return "";

        string result = to_string(node->val);
        string left = serialize(node->left);
        string right = serialize(node->right);

        if (!left.empty()) result += " " + left;
        if (!right.empty()) result += " " + right;

        return result;
    }

    // Preorder deserialization
    Node* deserialize(const string& serialized) {
        if (serialized.empty()) return nullptr;

        vector<int> items = split(serialized);
        int index = 0;
        return deserialize(items, index, INT_MIN, INT_MAX);
    }

   private:
    Node* deserialize(const vector<int>& items, int& index, int mn, int mx) {
        if (index >= items.size()) return nullptr;
        int val = items[index];
        if (val <= mn || val >= mx) return nullptr;

        Node* root = new Node(val);
        index++;

        root->left = deserialize(items, index, mn, val);
        root->right = deserialize(items, index, val, mx);

        return root;
    }

    // Helper: split a space-separated string into integers
    vector<int> split(const string& serialized) {
        vector<int> result;
        stringstream ss(serialized);
        int val;
        while (ss >> val) {
            result.push_back(val);
        }
        return result;
    }

    vector<int> split2(const string& serialized) {
        vector<int> result;
        char delim = ' ';
        size_t pos = 0;
        size_t nextpos = string::npos;
        while ((nextpos = serialized.find(pos, delim)) != string::npos) {
            string word = serialized.substr(pos, nextpos - pos - 1);
            result.push_back(stoi(word));
        }

        return result;
    }
};