#pragma once
#include "../header.h"
#include "tree/Tree.h"

class SerializeDeserializeBT {
   public:
    static void test() {
        SerializeDeserializeBT obj;
        Tree<int> tree;
        tree.root = new Tree<int>::Node(23);
        tree.root->left = new Tree<int>::Node(1);
        tree.root->right = new Tree<int>::Node(51);
        tree.root->left->right = new Tree<int>::Node(20);
        tree.root->right->left = new Tree<int>::Node(2);

        cout << "Original: " << tree.inorder() << endl;

        string serialized = obj.serialize(tree.root);
        cout << "Serialized :" << serialized << endl;

        Tree<int> deserializeTree;
        deserializeTree.root = obj.deserialize(serialized);
        cout << "Deserialized:" << deserializeTree.inorder() << endl;
    }

   public:
    string serialize(Tree<int>::Node* node) {
        if (!node) return "#";

        string result = std::to_string(node->val);

        result += " " + serialize(node->left);
        result += " " + serialize(node->right);

        return result;
    }

    Tree<int>::Node* deserialize(string serilized) {
        vector<int> items = split(serilized);
        int index = 0;

        return deserialize(items, index, INT_MIN);
    }

    Tree<int>::Node* deserialize(const vector<int>& items, int& index, int marker) {
        if (index >= items.size()) return nullptr;
        if (items[index] == marker) return nullptr;

        Tree<int>::Node* root = new Tree<int>::Node(items[index++]);

        root->left = deserialize(items, index, marker);
        root->right = deserialize(items, index, marker);

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
};