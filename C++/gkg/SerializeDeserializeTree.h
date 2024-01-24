#pragma once
#include "../Header.h"

class SerializeDeserializeTree {
public:
    static void test() {
        SerializeDeserializeTree obj;
        BinaryTreeNode<int>* root = new BinaryTreeNode<int>(1);
        root->left = new BinaryTreeNode<int>(2);
        root->right = new BinaryTreeNode<int>(3);
        root->left->left = new BinaryTreeNode<int>(4);
        root->right->left = new BinaryTreeNode<int>(5);
        root->right->right = new BinaryTreeNode<int>(6);

        cout << "Tree: " << endl;
        cout << to_string(root);
        cout << endl;

        string fileName = "tree.data";
        obj.serialize(root, fileName);

        BinaryTreeNode<int>* newRoot = obj.deserialize(fileName);
        cout << "Tree: " << endl;
        cout << to_string(root);
        cout << endl;
    }

    void serialize(BinaryTreeNode<int>* root, string fileName) {
        ofstream out(fileName);
        serialize(root, out);
    }

    BinaryTreeNode<int>* deserialize(string fileName) {
        ifstream in(fileName);
        return deserialize(in);
    }

private:
    void serialize(BinaryTreeNode<int>* root, ofstream& out) {
        if (!root) {
            out << INT_MIN << " ";
            return;
        }
        out << root->val << " ";
        serialize(root->left, out);
        serialize(root->right, out);
    }

    BinaryTreeNode<int>* deserialize(ifstream& in) {
        int val;
        if (!(in >> val) || val == INT_MIN) return nullptr;
        BinaryTreeNode<int>* cur = new BinaryTreeNode<int>(val);
        cur->left = deserialize(in);
        cur->right = deserialize(in);

        return cur;
    }
};