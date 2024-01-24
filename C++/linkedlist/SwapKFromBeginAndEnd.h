#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;

class Node
{
public:
    int val;
    Node* next;
    Node(int val, Node* next = nullptr) : val(val), next(next)
    {
    }
};

class LinkedList
{
public:
    Node* root = nullptr;

    LinkedList(vector<int> v)
    {
        Node* tmp = root;
        for (auto i : v) {
            if (root == nullptr) root = tmp = new Node(i);
            else { tmp->next = new Node(i); tmp = tmp->next; }
        }
    }

    string str()
    {
        stringstream ss;
        Node* tmp = root;
        while (tmp != nullptr) {
            ss << tmp->val << " "; tmp = tmp->next;
        }
        return ss.str();
    }
};

class SwapKFromBeginAndEnd
{
public:
    static void test(LinkedList* l, int k)
    {
        SwapKFromBeginAndEnd obj;
        cout << "Input: ";
        cout << l->str();
        cout << ", k = " << k << endl;
        cout << "Output: ";
        bool res = obj.swapNodes(l, k);
        if (res) {
            cout << l->str() << endl;
        }
    }

    bool swapNodes(LinkedList* l, int k)
    {
        Node* kFromBegin = nullptr;
        Node* kFromEnd = nullptr;
        Node* tmp = l->root;
        int cnt = 0;

        while (tmp != nullptr)
        {
            cnt++;
            if (cnt == k) {
                kFromBegin = tmp; kFromEnd = l->root;
            }
            else if (cnt > k) {
                kFromEnd = kFromEnd->next;
            }

            tmp = tmp->next;
        }
        if (kFromBegin == nullptr || kFromEnd == nullptr)
        {
            cout << "List is smaller than K" << endl;
            return false;
        }
        swap(kFromBegin->val, kFromEnd->val);
        return true;
    }
};