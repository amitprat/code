#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Node
{
    int val;
    Node* left, * right;

    Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
};

class BinaryTree
{
public:
    static void testBinaryTree()
    {
        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);
        root->right->left = new Node(5);

        BinaryTree obj;
        cout << "Original Tree:";
        obj.printTree(root);
        cout << endl;

        Node* mirrorNode = obj.mirror(root);
        cout << "Mirror Tree:";
        obj.printTree(mirrorNode);
        cout << endl;

        bool res = obj.isMirror(root, mirrorNode);
        cout << "IsMirror: " << res << endl;

        obj.inplaceMirror(root);
        cout << "InPlace Mirror Tree:";
        obj.printTree(root);
        cout << endl;
    }

    Node* mirror(Node* node)
    {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->val);
        newNode->right = mirror(node->left);
        newNode->left = mirror(node->right);

        return newNode;
    }

    void inplaceMirror(Node*& node)
    {
        if (node == nullptr) return;
        swap(node->left, node->right);
        inplaceMirror(node->left);
        inplaceMirror(node->right);
    }

    bool isMirror(Node* originalNode, Node* mirrorNode)
    {
        if (originalNode == nullptr && mirrorNode == nullptr) return true;
        if (originalNode == nullptr || mirrorNode == nullptr) return false;

        return originalNode->val == mirrorNode->val &&
            isMirror(originalNode->left, mirrorNode->right) &&
            isMirror(originalNode->right, mirrorNode->left);
    }

    void printTree(Node* node) {
        if (node)
        {
            cout << node->val << " ";
            printTree(node->left);
            printTree(node->right);
        }
    }
};
