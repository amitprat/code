#pragma once
#include <cassert>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/**
 * Generic Doubly Linked List Template
 * ------------------------------------
 * Supports construction from vector, insertion, deletion, search,
 * reverse, splice, iterators, and full test coverage with assertions.
 */

template <class T>
class LinkedList {
   public:
    class Node {
       public:
        T val;
        Node* prev = nullptr;
        Node* next = nullptr;

        Node(T val, Node* prev = nullptr, Node* next = nullptr)
            : val(val), prev(prev), next(next) {}

        string to_string() const {
            return std::to_string(val);
        }
    };

   private:
    Node* head = nullptr;
    int sz = 0;

   public:
    LinkedList() = default;

    ~LinkedList() {
        clear();
    }

    Node* getHead() const {
        return head;
    }

    Node* setHead(Node* newHead) {
        this->head = newHead;
    }

    explicit LinkedList(const vector<T>& arr) {
        for (const auto& e : arr) push_back(e);
    }

    LinkedList<T>& push_front(T val) {
        Node* node = new Node(val);
        node->next = head;
        if (head) head->prev = node;
        head = node;

        ++sz;

        return *this;
    }

    LinkedList<T>& push_back(T val) {
        Node* node = new Node(val);
        if (!head) {
            head = node;
        } else {
            Node* tmp = head;
            while (tmp->next) tmp = tmp->next;
            tmp->next = node;
            node->prev = tmp;
        }

        ++sz;

        return *this;
    }

    void pop_front() {
        if (!head) return;

        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        delete tmp;

        --sz;
    }

    void pop_back() {
        if (!head) return;

        if (!head->next) {
            delete head;

            head = nullptr;
            --sz;

            return;
        }

        Node* tmp = head;
        while (tmp->next) tmp = tmp->next;
        tmp->prev->next = nullptr;
        delete tmp;

        --sz;
    }

    Node* find(const T& val) const {
        Node* tmp = head;
        while (tmp) {
            if (tmp->val == val) return tmp;
            tmp = tmp->next;
        }

        return nullptr;
    }

    void reverse() {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            Node* next = current->next;
            current->next = prev;
            prev->prev = current;
            prev = current;
            current = next;
        }
        head = prev;
    }

    void insert_at(int index, T val) {
        if (index < 0 || index > sz) return;
        if (index == 0) {
            push_front(val);
            return;
        }

        Node* tmp = head;
        for (int i = 0; i < index - 1 && tmp; ++i) tmp = tmp->next;
        if (!tmp) return;

        Node* node = new Node(val);
        node->next = tmp->next;
        node->prev = tmp;
        if (tmp->next) tmp->next->prev = node;
        tmp->next = node;
        ++sz;
    }

    void erase_at(int index) {
        if (index < 0 || index >= sz) return;

        if (index == 0) {
            pop_front();
            return;
        }

        Node* tmp = head;
        for (int i = 0; i < index && tmp; ++i) tmp = tmp->next;
        if (!tmp) return;

        if (tmp->prev) tmp->prev->next = tmp->next;
        if (tmp->next) tmp->next->prev = tmp->prev;
        delete tmp;

        --sz;
    }

    void clear() {
        while (head) pop_front();
        sz = 0;
    }

    int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    // Iterator support
    class Iterator {
        Node* current;

       public:
        explicit Iterator(Node* node) : current(node) {}
        T& operator*() const { return current->val; }
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    class ReverseIterator {
        Node* current;

       public:
        explicit ReverseIterator(Node* node) : current(node) {}
        T& operator*() const { return current->val; }
        ReverseIterator& operator++() {
            current = current->prev;
            return *this;
        }
        bool operator!=(const ReverseIterator& other) const { return current != other.current; }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

    ReverseIterator rbegin() const {
        Node* tmp = head;
        while (tmp && tmp->next) tmp = tmp->next;
        return ReverseIterator(tmp);
    }

    ReverseIterator rend() const { return ReverseIterator(nullptr); }

    void splice(LinkedList<T>& other) {
        if (!other.head) return;

        if (!head) {
            head = other.head;
        } else {
            Node* tail = head;
            while (tail->next) tail = tail->next;
            tail->next = other.head;
            other.head->prev = tail;
        }
        sz += other.sz;
        other.head = nullptr;
        other.sz = 0;
    }

    string to_string() const {
        stringstream ss;

        Node* tmp = head;
        while (tmp) {
            ss << tmp->val;
            if (tmp->next) ss << " ";
            tmp = tmp->next;
        }

        return ss.str();
    }

    friend ostream& operator<<(ostream& out, const LinkedList<T>& list) {
        out << "{";
        Node* node = list.head;
        while (node) {
            out << node->to_string();
            if (node->next) out << ", ";
            node = node->next;
        }
        out << "}";
        return out;
    }

    static size_t length(const Node* cur) {
        size_t len = 0;
        while (cur) {
            len++;
            cur = cur->next;
        }
        return len;
    }

    static string to_string(const Node* cur) {
        stringstream ss;
        ss << "{";
        while (cur) {
            ss << cur->to_string();
            if (cur->next) ss << ", ";
            cur = cur->next;
        }
        ss << "}";

        return ss.str();
    }

    static void test() {
        LinkedList<int> list;
        assert(list.empty());
        list.push_back(1).push_back(2).push_back(3);
        assert(list.size() == 3);
        assert(list.to_string() == "1 2 3");

        list.push_front(0);
        assert(list.to_string() == "0 1 2 3");

        list.insert_at(2, 99);
        assert(list.to_string() == "0 1 99 2 3");

        list.erase_at(2);
        assert(list.to_string() == "0 1 2 3");

        list.pop_back();
        assert(list.to_string() == "0 1 2");

        list.pop_front();
        assert(list.to_string() == "1 2");

        assert(list.find(2));
        assert(!list.find(42));

        list.reverse();
        assert(list.to_string() == "2 1");

        list.clear();
        assert(list.empty());

        LinkedList<int> a({1, 2, 3});
        LinkedList<int> b({4, 5});
        a.splice(b);
        assert(a.to_string() == "1 2 3 4 5");
        assert(b.empty());

        string r;
        for (auto it = a.rbegin(); it != a.rend(); ++it) r += std::to_string(*it) + " ";
        assert(r == "5 4 3 2 1 ");

        string f;
        for (int x : a) f += std::to_string(x) + " ";
        assert(f == "1 2 3 4 5 ");
    }
};
