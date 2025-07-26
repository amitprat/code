#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../header.h"
using namespace std;

class ValidTree {
   public:
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node() : val(0), left(nullptr), right(nullptr) {}
        Node(int v, Node* l = nullptr, Node* r = nullptr) : val(v), left(l), right(r) {}
    };

    static void test() {
        ValidTree obj;
        {
            cout << "Validate empty list, Should be valid: ";
            vector<Node*> list;
            cout << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate single root node, Should be valid: ";
            Node* root = new Node(1);
            vector<Node*> list = {root};
            cout << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate full tree, Should be valid: ";
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            vector<Node*> list = {root->left, root->right, root};
            cout << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate missing node, Should be invalid: ";
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            vector<Node*> list = {root->left, root};  // missing root->right
            cout << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate cycle, Should be invalid: ";
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->left->right = root->right;  // cycle
            vector<Node*> list = {root, root->left, root->right};
            cout << obj.isValidTree(list) << endl;
        }
    }

   public:
    bool isValidTree(const vector<Node*>& list) {
        if (list.empty()) return true;

        unordered_set<Node*> nodes(list.begin(), list.end());
        unordered_map<Node*, Node*> parent;  // child -> parent

        // Check missing children and multiple parents
        for (auto n : list) {
            if (n->left) {
                if (nodes.find(n->left) == nodes.end()) {
                    cout << "Missing node in list" << endl;
                    return false;
                }
                if (parent.find(n->left) != parent.end()) {
                    cout << "Node has multiple parents" << endl;
                    return false;
                }
                parent[n->left] = n;
            }
            if (n->right) {
                if (nodes.find(n->right) == nodes.end()) {
                    cout << "Missing node in list" << endl;
                    return false;
                }
                if (parent.find(n->right) != parent.end()) {
                    cout << "Node has multiple parents" << endl;
                    return false;
                }
                parent[n->right] = n;
            }
        }

        // Find root(s)
        Node* root = nullptr;
        for (auto n : list) {
            if (parent.find(n) == parent.end()) {
                if (root) {
                    cout << "Multiple roots found" << endl;
                    return false;
                }
                root = n;
            }
        }

        if (!root) {
            cout << "No root found" << endl;
            return false;
        }

        // Detect cycles using DFS
        unordered_set<Node*> visited;
        if (!dfs(root, visited)) {
            cout << "Cycle detected" << endl;
            return false;
        }

        // Check all nodes reachable
        if (visited.size() != list.size()) {
            cout << "Disconnected nodes exist" << endl;
            return false;
        }

        return true;
    }

   private:
    bool dfs(Node* node, unordered_set<Node*>& visited) {
        if (!node) return true;
        if (visited.count(node)) return false;  // cycle detected

        visited.insert(node);
        return dfs(node->left, visited) && dfs(node->right, visited);
    }
};