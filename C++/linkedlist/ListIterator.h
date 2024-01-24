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
#include <functional>
#include <future>
#include "AsyncState.h"
using namespace std;

template <typename T>
class List
{
public:
    class Node {
    public:
        T val;
        Node* next;
        Node* prev;

        Node(T val, Node* next = nullptr, Node* prev = nullptr)
        {
            this->val = val;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    public:
        Iterator() :root(nullptr) {}
        Iterator(Node* root) : root(root) {}
        Iterator& operator=(Node* node) {
            this->node = node;
            return *this;
        }

        Iterator& operator++() {
            if (root) {
                root = root->next;
            }
            return *this;
        }

        Iterator& operator++(int) {
            Iterator iter = *this;
            ++* this;
            return iter;
        }

        bool operator!=(const Iterator& other) {
            return root != other.root;
        }

        T operator*() {
            return root->val;
        }
    private:
        Node* root;
    };

    Iterator begin()
    {
        return Iterator(root);
    }

    Iterator end()
    {
        return Iterator();
    }

    void add(T val);

private:
    Node* root = nullptr;
};

template <typename T>
void List<T>::add(T val)
{
    if (root == nullptr) {
        root = new Node(val);
    }
    else {
        Node* tmp = root;
        while (tmp->next) { tmp = tmp->next; }
        tmp->next = new Node(val);
    }
}

class ListIteratorTest
{
public:
    static void test()
    {
        List<int> l;
        l.add(1);
        l.add(2);
        l.add(3);
        l.add(4);

        for (auto i : l) {
            cout << i << " ";
        }
        cout << endl;
    }
};