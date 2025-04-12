#pragma once
#include "../header.h"
#include "BinaryTree.h"

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

        cout << "Original: " << (new BinaryTree<int>(root))->inorder() << endl;

        string serialized = obj.serialize(root);
        cout << "Serialized :" << serialized << endl;

        Node* deserialized = obj.deserialize(serialized);
        cout << "Deserialized:" << (new BinaryTree<int>(deserialized))->inorder() << endl;
    }

   public:
    string serialize(Node* node) {
        if (!node) return "";

        string result;
        result += std::to_string(node->val);

        string left = serialize(node->left);
        if (!left.empty()) result += " " + left;

        string right = serialize(node->right);
        if (!right.empty()) result += " " + right;

        return result;
    }

    Node* deserialize(string serilized) {
        vector<int> items = split(serilized);

        int index = 0;
        return deserialize(items, index, INT_MIN, INT_MAX);
    }

    Node* deserialize(vector<int> items, int& index, int mn, int mx) {
        if (index >= items.size()) return nullptr;
        if (items[index] <= mn || items[index] >= mx) return nullptr;

        Node* root = new Node(items[index++]);
        root->left = deserialize(items, index, mn, items[index]);
        root->right = deserialize(items, index, items[index], mx);

        return root;
    }

   private:
    vector<int> split(string serialized) {
        vector<int> result;
        stringstream ss(serialized);
        string word;
        while (ss >> word) {
            result.push_back(stoi(word));
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