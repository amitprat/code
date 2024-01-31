#pragma once
#include "../header.h"

template <class T>
struct Node {
    T val;
    Node(T val) : val(val) {}
};

template <class T>
class Base {
   public:
    Node<T>* root;

    void print() {
        cout << root->val << endl;
    }
};