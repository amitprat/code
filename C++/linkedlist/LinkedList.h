#pragma once
#include "../header.h"

template <class T>
class LinkedList {
    class Node {
       public:
        T val;
        Node* next = nullptr;
        Node(T val, Node* next = nullptr) : val(val), next(next) {}
    };

    Node* head = nullptr;

   public:
    LinkedList<T>& push_front(int val) {
        if (!head)
            head = new Node(data);
        else {
            Node* tmp = new Node(data);
            tmp->next = head;
            head = tmp;
        }

        return *this;
    }

    LinkedList<T>& push_back(T val) {
        if (head == nullptr)
            head = new Node(val);
        else {
            Node* tmp = head;
            while (tmp->next) tmp = tmp->next;
            tmp->next = new Node(val);
        }
        return *this;
    }

    string to_string() {
        stringstream ss;
        Node* tmp = head;
        while (tmp) {
            ss << tmp->val << " ";
            tmp = tmp->next;
        }
        ss.seekg(-1);
        return ss.str();
    }

    int length(Node* head) {
        int sz = 0;
        while (head) {
            sz++;
            head = head->next;
        }

        return sz;
    }

    Node* get_head() {
        return head;
    }

    void set_head(Node* newHead) {
        head = newHead;
    }

    bool empty() {
        return head == nullptr;
    }

    friend ostream& operator<<(ostream& out, Node* head) {
        out << "{";
        while (head) {
            out << head->to_string() << ", ";
            head = head->next;
        }
        out << "}";

        return out;
    }
};