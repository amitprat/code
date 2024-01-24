#pragma once
#include "../header.h"
#include "LinkedList.h"

class IsLinkedListPalin {
public:
    static void test() {
        IsLinkedListPalin obj;
        {
            LinkedList<int> list;
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;

        {
            LinkedList<int> list;
            list.add(1);
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;

        {
            LinkedList<int> list;
            list.add(1).add(1);
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;

        {
            LinkedList<int> list;
            list.add(1).add(2);
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;

        {
            LinkedList<int> list;
            list.add(1).add(2).add(1);
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;

        {
            LinkedList<int> list;
            list.add(1).add(2).add(2).add(1);
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;

        {
            LinkedList<int> list;
            list.add(1).add(2).add(2).add(1).add(3);
            cout << "Is linked list: " << list.to_string() << ", is palin: " << obj.isPalin3(list) << endl;
        }
        cout << endl;
    }

    void print(Node<int>* node) {
        cout << "LinkedList: ";
        while (node) {
            cout << node->val << " ";
            node = node->next;
        }
        cout << endl;
    }

    bool isPalin(LinkedList<int> list) {
        Node<int>* start = list.getRaw();
        Node<int>* end = reverseClone(list.getRaw());
        print(start);
        print(end);

        while (start && end) {
            if (start->val != end->val) return false;
            start = start->next;
            end = end->next;
        }

        return true;
    }

    bool isPalin2(LinkedList<int> list) {
        Node<int>* node = list.getRaw();
        return isPalin(node, node);
    }

    bool isPalin3(LinkedList<int> list) {
        stack<Node<int>* > st;
        Node<int>* slow, * fast;
        slow = fast = list.getRaw();

        while (fast && fast->next) {
            st.push(slow);
            slow = slow->next;
            fast = fast->next->next;
        }
        if (fast != nullptr) if (!st.empty()) st.pop();
        else slow = slow->next;

        while (!st.empty() && slow) {
            if (st.top()->val != slow->val) return false;
            slow = slow->next;
            st.pop();
        }
        return st.empty() && !slow;
    }

private:
    bool isPalin(Node<int>*& start, Node<int>* end) {
        if (end == nullptr) return true;
        bool res = isPalin(start, end->next);
        if (!res || (start->val != end->val)) return false;
        start = start->next;
        return true;
    }

    Node<int>* reverseClone(Node<int>* node) {
        Node<int>* prev = nullptr;
        while (node) {
            auto* clone = new Node<int>(node->val);
            clone->next = prev;
            prev = clone;
            node = node->next;
        }
        return prev;
    }
};