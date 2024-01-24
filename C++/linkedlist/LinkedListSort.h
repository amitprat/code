#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

template <class T>
class Node
{
public:
    T val;
    Node* next;

    Node(T val, Node* next = nullptr) : val(val), next(next) {}
};
template <class T>
class LinkedList
{
    Node<T>* root = nullptr;
    int size = 0;
public:
    LinkedList(vector<int> v) {
        for (auto i : v) add(i);
        size = v.size();
    }
    LinkedList(Node<T>* root, int size) :root(root), size(size) {}

    LinkedList& add(int val) {
        if (root == nullptr) root = new Node<T>(val);
        else {
            Node<T>* tmp = root;
            while (tmp->next != nullptr) tmp = tmp->next;
            tmp->next = new Node<T>(val);
        }
        size++;
        return *this;
    }

    string str()
    {
        stringstream out;
        Node<T>* tmp = root;
        out << "{";
        while (tmp != nullptr) {
            out << tmp->val << " ";
            tmp = tmp->next;
        }
        out << "}";

        return out.str();
    }

    int length() {
        return size;
    }

    Node<T>* getRoot() {
        return root;
    }
};

class LinkedListSort
{
public:
    void test()
    {
        vector<LinkedList<int>*> v = {
            new LinkedList<int>({}),
            new LinkedList<int>({0}),
            new LinkedList<int>({1,2}),
            new LinkedList<int>({2,1}),
            new LinkedList<int>({3,1,2}),
            new LinkedList<int>({3,2,1}),
            new LinkedList<int>({1,2,3}),
            new LinkedList<int>({10, 12, 20, 30, 25,40, 32, 31, 35, 50, 60})
        };

        for (auto arr : v) {
            cout << "Processing= " << arr->str();
            cout << " : ";
            sort(arr, 0, arr->length());
            cout << "Sorted = " << arr->str() << endl;
        }
    }

    void sort(LinkedList<int>*& list, int l, int r)
    {
        if (l < r) {
            int m = (l + r) / 2;
            LinkedList<int>* first = nullptr;
            LinkedList<int>* second = nullptr;
            devide(list, l, m, r, first, second);
            sort(first, l, m);
            sort(second, m + 1, r);
            list = merge(first, second);
        }
    }

    void devide(LinkedList<int>* list, int l, int m, int r, LinkedList<int>*& first, LinkedList<int>*& second)
    {
        Node<int>* firstRoot = list->getRoot();
        Node<int>* secondRoot = list->getRoot();
        Node<int>* tmp = firstRoot;
        int sz = 0;
        while (sz < m - l) {
            tmp = tmp->next;
            sz++;
        }
        secondRoot = tmp->next;
        tmp->next = nullptr;

        first = new LinkedList<int>(firstRoot, sz + 1);
        second = new LinkedList<int>(secondRoot, r - sz - 1);
    }

    LinkedList<int>* merge(LinkedList<int>* first, LinkedList<int>* second)
    {
        Node<int>* root = new Node<int>(-1);
        Node<int>* rootFirst = first->getRoot();
        Node<int>* rootSecond = second->getRoot();

        Node<int>* tmp = root;
        int size = 0;
        while (rootFirst && rootSecond) {
            if (rootFirst->val < rootSecond->val) {
                tmp->next = rootFirst; rootFirst = rootFirst->next;
            }
            else {
                tmp->next = rootSecond; rootSecond = rootSecond->next;
            }
            size++;
            tmp = tmp->next;
        }
        while (rootFirst) { tmp->next = rootFirst; tmp = tmp->next; rootFirst = rootFirst->next; size++; }
        while (rootSecond) { tmp->next = rootSecond; tmp = tmp->next; rootSecond = rootSecond->next; size++; }

        return new LinkedList<int>(root->next, size);
    }
};