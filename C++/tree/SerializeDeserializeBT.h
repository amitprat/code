#pragma once
#include "../header.h"
#include "BinaryTree.h"

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

        cout << "Original: " << (new BinaryTree<int>(root))->inorder() << endl;

        string serialized = obj.serialize(root);
        cout << "Serialized :" << serialized << endl;

        root = obj.deserialize(serialized);
        cout << "Deserialized:" << (new BinaryTree<int>(root))->inorder() << endl;
    }

   public:
    // Do preorder iterate and serialize the string with "#" for nullptr for marking.
    string serialize(Node* node) {
        if (!node) return "#";

        string result = std::to_string(node->val);

        result += " " + serialize(node->left);
        result += " " + serialize(node->right);

        return result;
    }

   public:
    Node* deserialize(string serilized) {
        vector<string> items = split(serilized);
        int index = 0;

        return deserialize(items, index, "#");
    }

    Node* deserialize(const vector<string>& items, int& index, string marker) {
        if (index >= items.size()) return nullptr;
        if (items[index++] == marker) return nullptr;

        Node* root = new Node(stoi(items[index]));
        root->left = deserialize(items, index, marker);
        root->right = deserialize(items, index, marker);

        return root;
    }

   private:
    vector<string> split(string serialized) {
        vector<string> result;
        stringstream ss(serialized);  // gets space seperated string to words

        string word;
        while (ss >> word) {  // iterate through all words and convert to int and push to vector
            result.push_back(word);
        }

        return result;
    }
};