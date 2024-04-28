#pragma once
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class LinkedList {
   public:
    class Node {
       public:
        T val;

        Node* prev = nullptr;
        Node* next = nullptr;
        Node(T val, Node* prev = nullptr, Node* next = nullptr) : val(val), prev(prev), next(next) {}

        string to_string() {
            return std::to_string(val);
        }
    };

    Node* head = nullptr;

   public:
    LinkedList() {
    }
    LinkedList(const vector<T>& arr) {
        head = create(arr);
    }

    static Node* create(const vector<T>& arr) {
        Node* head = new Node(-1);  // dummy
        Node* tail = head;
        for (auto& e : arr) {
            tail->next = new Node(e);
            tail->next->prev = tail;

            tail = tail->next;
        }

        auto next = head->next;
        delete head;

        head = next;
        head->prev = nullptr;

        return head;
    }

    LinkedList<T>& push_front(T val) {
        if (!head) {
            head = new Node(val);
        } else {
            Node* tmp = new Node(val);
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

    static int length(Node* head) {
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

    friend ostream& operator<<(ostream& out, const LinkedList<T>& cur) {
        auto node = cur->head;

        out << "{";
        while (node) {
            out << node->to_string() << ", ";
            node = node->next;
        }
        out << "}";

        return out;
    }
};