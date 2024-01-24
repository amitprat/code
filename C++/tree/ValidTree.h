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
#include <mutex>
#include <cassert>
#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class ValidTree
{
public:
    struct Node {
        int val;
        Node* left, * right;
        Node() {}
        Node(int val, Node* left = nullptr, Node* right = nullptr) : val(val), left(left), right(right) {}
    };
    static void test()
    {
        ValidTree obj;
        {
            cout << "Validate empty list, Should be valid" << endl;
            vector<Node*> list;
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate root node list, Should be valid" << endl;
            Node* root = new Node(1);
            vector<Node*> list = {
                root
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate subtree node list, Should be valid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            vector<Node*> list = {
                root->left
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate one node root list, Should be valid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            vector<Node*> list = {
                root->left,root
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate full node list, Should be valid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            vector<Node*> list = {
                root->right, root->left, root
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate full node list, Should be valid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->right->right = new Node(4);
            vector<Node*> list = {
                root->right, root->left, root, root->right->right
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate missing node list, Should be invalid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->right->right = new Node(4);
            vector<Node*> list = {
                root->right, root->left, root
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate missing node list, Should be invalid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->left->right = root->right;
            root->right->right = new Node(4);
            vector<Node*> list = { root
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate circular node list, Should be invalid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->left->right = root->right;
            root->right->right = new Node(4);
            vector<Node*> list = { root, root->right->right, root->right, root->left->right
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }

        {
            cout << "Validate tmp node list, Should be invalid" << endl;
            Node* root = new Node(1);
            root->left = new Node(2);
            root->right = new Node(3);
            root->right->right = new Node(4);

            Node* tmp = new Node(5);
            vector<Node*> list = { root, root->right->right, root->right,tmp
            };
            cout << "Tree is Valid? :" << obj.isValidTree(list) << endl;
        }
    }

    bool isValidTree(vector<Node*> list) {
        unordered_set<Node*> set;
        for (auto i : list) set.insert(i);

        unordered_map<Node*, vector<Node*>> map;
        for (auto n : list) {
            if (n->left) {
                if (set.find(n->left) == set.end()) {
                    cout << "Missing node in list";
                    return false;
                }
                map[n->left].push_back(n);
            }
            if (n->right) {
                if (set.find(n->right) == set.end()) {
                    cout << "Missing node in list";
                    return false;
                }
                map[n->right].push_back(n);
            }
        }
        int rootCount = 0;
        for (auto i : list) {
            if (map.find(i) == map.end()) {
                rootCount++;
            }
            if (rootCount > 1) {
                cout << "Dangling Node" << endl;
                return false;
            }
        }

        for (auto m : map) {
            if (m.second.size() > 1) {
                cout << "Found circle" << endl;
                return false;
            }
        }
        return true;
    }
};