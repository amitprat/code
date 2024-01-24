#pragma once
#include "../header.h"

namespace specialstack {
    template <class T>
    class Node {
    public:
        T val;
        Node<T>* prev, * next;
        Node(T val) : val(val), prev(nullptr), next(nullptr) {}
    };
    template <class T>
    class LinkedList
    {
    private:
        int size = 0;
        Node<T>* head = nullptr;
        Node<T>* middle = nullptr;
    public:
        void push_front(T elem) {
            if (head == nullptr) head = new Node<T>(elem);
            else {
                auto node = new Node<T>(elem);
                node->next = head;
                head->prev = node;
                head = node;
            }
            size++;
            if (middle == nullptr) middle = head;
            else if (size % 2 == 1) middle = middle->prev;
        }
        T pop_front() {
            if (head == nullptr) throw exception("Empty linked list");
            auto cur = head;
            head = head->next;
            size--;
            if (size == 0) middle = nullptr;

            return cur->val;
        }
        T removeMid() {
            if (middle->next != nullptr) {
                middle->next->prev = middle->prev;
                middle->prev->next = middle->next;
            }

            auto tmp = middle->next;
            auto val = middle->val;
            delete middle;
            size--;

            middle = tmp;
            return val;
        }

        T getMid() {
            return middle->val;
        }
        bool empty() {
            return head == nullptr;
        }
    };
    class Stack {
    private:
        LinkedList<int>* head = nullptr;

    public:
        Stack() {
            head = new LinkedList<int>();
        }
        void push(int elem) {
            head->push_front(elem);
        }
        int pop() {
            if (head->empty()) throw exception("Empty linked list");
            auto elem = head->pop_front();
            return elem;
        }
        int getMid() {
            if (head->empty()) throw exception("Empty linked list");
            return head->getMid();
        }
        void deleteMid() {
            if (head->empty()) throw exception("Empty linked list");
            head->removeMid();
        }
        bool empty() {
            return head->empty();
        }

        static void test() {
            Stack st;
            auto add = [st](auto elem) mutable {
                cout << "Pushing elem: " << elem << endl;
                st.push(elem);
            };
            auto mid = [st]() mutable {
                cout << "Mid element: " << st.getMid() << endl;
            };
            auto delMid = [st]() mutable {
                cout << "Deleting Mid element: " << st.getMid() << endl;
                st.deleteMid();
            };
            auto print = [st]() mutable {
                cout << "Current state of stack: ";
                while (!st.empty()) cout << st.pop() << " ";
                cout << endl;
            };

            add(1); mid();
            add(2); mid();
            add(3); mid();

            delMid();

            print();

            add(1); mid();
            add(2); mid();
            add(3); mid();
            add(4); mid();
            add(5); mid();
            add(6); mid();
            add(7); mid();
            add(8); mid();
            add(9); mid();

            delMid();
            delMid();
            delMid();

            print();
        }
    };
}