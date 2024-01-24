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
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

template <class T>
class LinkedList {
public:
    class Node {
    public:
        T val;
        Node* next;
        Node() {}
        Node(T val) :val(val), next(nullptr) {}
    };

private:
    Node* root = nullptr;

public:
    LinkedList() {}

    Node*& getRoot() { return root; }
    void setRoot(Node* root) { this->root = root; }

    void add(T val) {
        if (!root) root = new Node(val);
        else {
            Node* tmp = root;
            while (tmp->next != nullptr) tmp = tmp->next;
            tmp->next = new Node(val);
        }
    }

    void print() {
        Node* tmp = root;
        while (tmp)
        {
            cout << tmp->val << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
};

class LinkedListMergeSort
{
public:
    static void test() {
        LinkedListMergeSort obj;
        {
            LinkedList<int> l;
            l.print();

            obj.sort(l.getRoot());
            l.print();
        }

        {
            LinkedList<int> l;
            l.add(4);
            l.print();

            obj.sort(l.getRoot());
            l.print();
        }

        {
            LinkedList<int> l;
            l.add(4);
            l.add(2);
            l.print();

            obj.sort(l.getRoot());
            l.print();
        }

        {
            LinkedList<int> l;
            l.add(4);
            l.add(2);
            l.add(3);
            l.print();

            obj.sort(l.getRoot());
            l.print();
        }

        {
            LinkedList<int> l;
            l.add(4);
            l.add(2);
            l.add(3);
            l.add(0);
            l.print();

            obj.sort(l.getRoot());
            l.print();
        }
    }

    void sort(LinkedList<int>::Node*& node) {
        if (node == nullptr || node->next == nullptr) return;
        LinkedList<int>::Node* first = nullptr;
        LinkedList<int>::Node* second = nullptr;

        split(node, first, second);
        sort(first);
        sort(second);

        node = merge(first, second);
    }

private:
    void split(LinkedList<int>::Node* root, LinkedList<int>::Node*& first, LinkedList<int>::Node*& second)
    {
        first = root;
        LinkedList<int>::Node* slow = root;
        LinkedList<int>::Node* fast = root->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        second = slow->next;
        slow->next = nullptr;
    }

    LinkedList<int>::Node* merge(LinkedList<int>::Node* first, LinkedList<int>::Node* second)
    {
        if (!first) return second;
        if (!second) return first;
        LinkedList<int>::Node* result;
        if (first->val < second->val) {
            result = first;
            result->next = merge(first->next, second);
        }
        else {
            result = second;
            result->next = merge(first, second->next);
        }

        return result;
    }
};