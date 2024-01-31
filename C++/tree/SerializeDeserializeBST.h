#pragma once
#include "../header.h"
#include "Tree.h"

class SerializeDeserializeBST {
   public:
    static void test() {
        SerializeDeserializeBST obj;

        Tree<int>* tree = new Tree<int>();
        tree->root = new Tree<int>::Node(3);
        tree->root->left = new Tree<int>::Node(1);
        tree->root->right = new Tree<int>::Node(5);
        tree->root->left->right = new Tree<int>::Node(2);
        tree->root->right->left = new Tree<int>::Node(4);

        cout << "Original: " << tree->inorder() << endl;

        string serialized = obj.serialize(tree->root);
        cout << "Serialized :" << serialized << endl;

        Tree<int>::Node* deserialized = obj.deserialize(serialized);
        Tree<int> deserializeTree;
        deserializeTree.root = deserialized;
        cout << "Deserialized:" << deserializeTree.inorder() << endl;
    }

   public:
    string serialize(Tree<int>::Node* node) {
        if (!node) return "";

        string result;
        result += std::to_string(node->val);

        string left = serialize(node->left);
        if (!left.empty()) result += " " + left;

        string right = serialize(node->right);
        if (!right.empty()) result += " " + right;

        return result;
    }

    Tree<int>::Node* deserialize(string serilized) {
        vector<int> items = split(serilized);
        return deserialize(items, 0, INT_MIN, INT_MAX);
    }

    Tree<int>::Node* deserialize(vector<int> items, int index, int mn, int mx) {
        if (index >= items.size()) return nullptr;
        if (items[index] <= mn || items[index] >= mx) return nullptr;

        Tree<int>::Node* root = new Tree<int>::Node(items[index]);
        root->left = deserialize(items, index + 1, mn, items[index]);
        root->right = deserialize(items, index + 1, items[index], mx);

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