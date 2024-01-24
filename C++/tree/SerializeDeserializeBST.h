#pragma once
#include "../Header.h"
using namespace std;

class BST
{
public:
    class Node
    {
    public:
        int val;
        Node* left, * right;
        Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };

    static void test()
    {
        BST obj;
        Node* node = new Node(3);
        node->left = new Node(1);
        node->right = new Node(5);
        node->left->right = new Node(2);
        node->right->left = new Node(4);

        cout << "Original: ";
        obj.print(node);
        cout << endl;

        string serialized = obj.serialize(node);
        cout << "Serialized :" << serialized << endl;

        Node* deserialized = obj.deserialize(serialized);
        cout << "De serialized:";
        obj.print(node);
    }

    void print(Node* node) {
        if (node) {
            print(node->left);
            cout << node->val << " ";
            print(node->right);
        }
    }

    string serialize(Node* node)
    {
        if (!node) return "";
        string result;
        result += std::to_string(node->val);
        string left = serialize(node->left);
        if (!left.empty()) result += " " + left;

        string right = serialize(node->right);
        if (!right.empty()) result += " " + right;

        return result;
    }

    Node* deserialize(string serilized)
    {
        vector<int> items = split(serilized);
        return deserialize(items, 0, INT_MIN, INT_MAX);
    }

    Node* deserialize(vector<int> items, int index, int mn, int mx)
    {
        if (index >= items.size()) return nullptr;
        if (items[index] <= mn || items[index] >= mx) return nullptr;
        Node* root = new Node(items[index]);
        root->left = deserialize(items, index + 1, mn, items[index]);
        root->right = deserialize(items, index + 1, items[index], mx);

        return root;
    }

    vector<int> split(string serialized)
    {
        vector<int> result;
        for (char ch : serialized) {
            if (ch == ' ') continue;
            result.push_back(ch - '0');
        }
        return result;
    }
};