#pragma once
#include "../header.h"

template <class T>
class Node {
public:
    T val;
    Node* next = nullptr;
    Node(T val, Node* next = nullptr) : val(val), next(next) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* head = nullptr;
public:
    LinkedList<T>& add(T val) {
        if (head == nullptr) head = new Node<T>(val);
        else {
            Node<T>* tmp = head;
            while (tmp->next) tmp = tmp->next;
            tmp->next = new Node<T>(val);
        }
        return *this;
    }

    string to_string() {
        stringstream ss;
        Node<T>* tmp = head;
        while (tmp) {
            ss << tmp->val << " ";
            tmp = tmp->next;
        }
        ss.seekg(-1);
        return ss.str();
    }

    Node<T>* getRaw() {
        return head;
    }

    void setRaw(Node<T>* newHead) {
        head = newHead;
    }

    bool empty() {
        return head == nullptr;
    }
};