#pragma once
#include <sstream>
#include <vector>

#include "../header.h"
#include "BinaryTree.h"
using namespace std;

class SerializeDeserializeBT {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        SerializeDeserializeBT obj;
        Node* root = new Node(23);
        root->left = new Node(1);
        root->right = new Node(51);
        root->left->right = new Node(20);
        root->right->left = new Node(2);

        cout << "Original inorder: " << (new BinaryTree<int>(root))->inorder() << endl;

        string serialized = obj.serialize(root);
        cout << "Serialized: " << serialized << endl;

        root = obj.deserialize(serialized);
        cout << "Deserialized inorder: " << (new BinaryTree<int>(root))->inorder() << endl;
    }

   public:
    // Preorder serialization with '#' for nulls
    string serialize(Node* node) {
        if (!node) return "#";

        string result = to_string(node->val);
        result += " " + serialize(node->left);
        result += " " + serialize(node->right);
        return result;
    }

    Node* deserialize(const string& serialized) {
        vector<string> items = split(serialized);
        int index = 0;
        return deserialize(items, index);
    }

   private:
    Node* deserialize(const vector<string>& items, int& index) {
        if (index >= items.size()) return nullptr;

        string val = items[index++];
        if (val == "#") return nullptr;

        Node* root = new Node(stoi(val));
        root->left = deserialize(items, index);
        root->right = deserialize(items, index);

        return root;
    }

    vector<string> split(const string& serialized) {
        vector<string> result;
        stringstream ss(serialized);
        string word;
        while (ss >> word) {
            result.push_back(word);
        }
        return result;
    }
};