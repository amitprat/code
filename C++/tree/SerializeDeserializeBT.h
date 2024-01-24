#pragma once
#include "../Header.h"
using namespace std;

class BT
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
        BT obj;
        Node* node = new Node(23);
        node->left = new Node(1);
        node->right = new Node(51);
        node->left->right = new Node(20);
        node->right->left = new Node(2);

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
        if (!node) return "#";
        string result;
        result += std::to_string(node->val);
        result += " " + serialize(node->left);
        result += " " + serialize(node->right);

        return result;
    }

    Node* deserialize(string serilized)
    {
        vector<int> items = split(serilized);
        int index = 0;
        return deserialize(items, index, INT_MIN);
    }

    Node* deserialize(vector<int> items, int& index, int marker)
    {
        if (index >= items.size()) return nullptr;
        if (items[index] == marker) return nullptr;
        Node* root = new Node(items[index++]);
        root->left = deserialize(items, index, marker);
        root->right = deserialize(items, index, marker);

        return root;
    }

    vector<int> split(string serialized)
    {
        vector<int> result;
        for (char ch : serialized) {
            if (ch == ' ') continue;
            if (ch == '#') result.push_back(INT_MIN);
            else result.push_back(ch - '0');
        }
        return result;
    }
};