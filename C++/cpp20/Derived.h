#pragma once
#include "../header.h"

template <class T>
class Base {
   public:
    struct Node {
        T val;
        Node(T val) : val(val) {}
    };

   public:
    Node* root;

    void print() {
        cout << root->val << endl;
    }
};

template <class T>
class Derived : public Base<T> {
   public:
    void set(T val) {
        root = new Node(val);
    }
};

class DerivedTest {
   public:
    static void test() {
        Derived<int> d;
        d.set(1);
        d.print();
    }
};