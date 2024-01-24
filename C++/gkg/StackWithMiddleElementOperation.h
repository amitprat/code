#pragma once
#include "../Header.h"

class StackWithMiddleElementOperation {
    class StackWithMiddleElement {
        struct Node {
            int item;
            Node* prev = nullptr;
            Node* next = nullptr;
            Node(int item) :item(item) {}
        };
        stack<Node*> st;
        stack<Node*> mid;
        int sz = 0;

    public:
        void push(int elem) {
            Node* node = new Node(elem);
            if (!st.empty()) {
                node->prev = st.top();
                st.top()->next = node;
            }
            st.push(node);
            sz++;
            if (sz & 1) {
                if (mid.empty()) mid.push(node);
                else mid.push(mid.top()->next);
            }
        }

        int pop() {
            if (st.empty()) return INT_MAX;

            auto val = st.top(); st.pop();
            if (sz & 1) mid.pop();

            sz--;

            return val->item;
        }

        int getMid() {
            return mid.top()->item;
        }

        int size()
        {
            return sz;
        }

        int top() { return st.top()->item; }
    };

    class StackWithMiddleElementV2 {
        struct Node {
            int item;
            Node* prev = nullptr;
            Node* next = nullptr;
            Node(int item) :item(item) {}
        };
        Node* head = nullptr;
        Node* mid = nullptr;
        int sz = 0;

    public:
        void push(int elem) {
            Node* node = new Node(elem);
            if (head) head->next = node;
            node->prev = head;
            head = node;
            sz++;
            if (sz & 1) {
                if (!mid) mid = node;
                else {
                    mid = mid->next;
                }
            }
        }

        int pop() {
            if (!head) return INT_MAX;

            auto val = head->item;
            auto prev = head->prev;
            delete head;
            head = prev;
            if (sz & 1) {
                mid = mid->prev;
            }

            sz--;

            return val;
        }

        int getMid() {
            if (empty()) return INT_MAX;
            return mid->item;
        }

        int deleteMid() {
            if (empty()) return INT_MAX;

            auto prev = mid->prev;
            auto next = mid->next;
            if (mid->prev) mid->prev->next = mid->next;
            if (mid->next) mid->next->prev = mid->prev;

            int val = mid->item;
            delete mid;
            mid = (sz & 1) ? prev : next;

            sz--;
            if (sz == 0) {
                head = mid = nullptr;
            }

            return val;
        }

        int size()
        {
            return sz;
        }

        int top() {
            if (empty()) return INT_MAX;
            return head->item;
        }

        bool empty() {
            return size() == 0;
        }
    };
public:
    static void test() {
        StackWithMiddleElementV2 st;

        for (int i = 1; i <= 10; i++) {
            st.push(i);
            cout << "Stack size: " << st.size() << endl;
            cout << "Stack last element: " << st.top() << endl;
            cout << "Stack Middle element: " << st.getMid() << endl;

            assert(st.size() == i);
            assert(st.top() == i);
            assert(st.getMid() == ((i - 1) / 2) + 1);
        }

        for (int i = 1; i <= 5; i++) {
            cout << "Stack last element popped: " << st.pop() << endl;
            cout << "Stack size: " << st.size() << endl;
            cout << "Stack Middle element: " << st.getMid() << endl;

            assert(st.size() == 10 - i);
            assert(st.top() == 10 - i);
            assert(st.getMid() == ((10 - i - 1) / 2) + 1);
        }

        for (int i = 1; i < 5; i++) {
            int ele = st.deleteMid();
            cout << "Stack Middle element deleted: " << ele << endl;
            cout << "Stack size: " << st.size() << endl;
            cout << "Stack last element: " << st.top() << endl;

            assert(st.size() == 5 - i);
            assert(st.top() == 5);
        }

        st.deleteMid();

        assert(st.size() == 0);
        assert(st.top() == INT_MAX);
        assert(st.getMid() == INT_MAX);
    }
};