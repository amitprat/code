#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class TernarySearchTree
{
private:
    struct Node
    {
        char val;
        bool isEnd;
        Node* left, * right, * equal;
        Node(char val) : val(val), isEnd(false), left(nullptr), right(nullptr), equal(nullptr) {}
    };
    Node* root = nullptr;

public:
    static void test()
    {
        TernarySearchTree obj;
        obj.insert("cat");
        obj.insert("cats");
        obj.insert("up");
        obj.insert("bug");

        obj.print();

        cout << obj.find("cats") << endl;
        cout << obj.find("bu") << endl;
        cout << obj.find("cat") << endl;
    }

    bool insert(string val)
    {
        root = insertRecur(root, val, 0);
        return true;
    }

    void print()
    {
        printRecur(root, "");
        cout << endl;
    }

    bool find(string val)
    {
        return findRecur(root, val, 0);
    }

    Node* insertRecur(Node* root, string val, int index)
    {
        if (!root) root = new Node(val[index]);
        if (val[index] < root->val) root->left = insertRecur(root->left, val, index);
        else if (val[index] > root->val) root->right = insertRecur(root->right, val, index);
        else {
            if (index == val.length() - 1) {
                root->isEnd = true;
            }
            else {
                root->equal = insertRecur(root->equal, val, index + 1);
            }
        }
        return root;
    }

    void printRecur(Node* root, string cur)
    {
        if (root) {
            if (!cur.empty())cur[cur.length() - 1] = root->val;
            else cur += root->val;
            printRecur(root->left, cur);
            if (root->isEnd) {
                cout << cur << " ";
            }
            printRecur(root->equal, cur + root->val);

            if (!cur.empty())cur[cur.length() - 1] = root->val;
            else cur += root->val;
            printRecur(root->right, cur);
        }
    }

    bool findRecur(Node* root, string val, int index)
    {
        if (root) {
            if (val[index] < root->val) return findRecur(root->left, val, index);
            else if (val[index] > root->val) return findRecur(root->right, val, index);
            else {
                if (index == val.length() - 1) return root->isEnd;
                else return findRecur(root->equal, val, index + 1);
            }
        }
        return false;
    }
};