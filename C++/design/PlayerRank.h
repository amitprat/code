#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
using namespace std;
using Data = pair<string, int>;

template <class T>
class BinarySearchTree
{
public:
    class Node
    {
    public:
        T val;
        int rank;
        Node* left, * right;
        Node(int val, int rank = 0, Node* left = nullptr, Node* right = nullptr) : val(val), rank(rank), left(left), right(right) {}
    };

    Node* root = nullptr;

    Node* insert(Data data)
    {
        if (!root) { root = new Node(data); return root; }
        if (data.second < root->val)
        {
            root->rank++;
            root->left = upsert(root->left, data);
        }
        else if (data.second > root->val)
        {
            root->rank++;
            root->right = upsert(root->right, data);
        }
        else {
            root->val = data;
        }

        return root;
    }
};

class PlayerRank
{
private:
    unordered_map<string, BinarySearchTree<Data>::Node*> map;
    BinarySearchTree<Data> tree;
public:
    static void test()
    {
        vector<Data> scores = { {"Carl", 70},{"Alex",55},{"Isla", 40} };
        PlayerRank obj;
        for (auto score : scores)
        {
            obj.upsert(score);
        }
        Data res = obj.getByRank(0);
        cout << "{" << res.first << ", " << res.second << "}" << endl;
    }

    bool upsert(const Data& score)
    {
        auto* item = tree.insert(score);
        map[score.first] = item;

        return true;
    }

    Data getByRank(int rank)
    {
    }
};