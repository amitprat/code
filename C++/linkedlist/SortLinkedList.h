#pragma  once

#include "../header.h"

class SortLinkedList {
    using Node = LinkedList<int>::Node;

public:
    static void test() {
        SortLinkedList obj;

        vector<LinkedList<int>> lists = {
                LinkedList<int>::create({}),
                LinkedList<int>::create({1}),
                LinkedList<int>::create({1, 2}),
                LinkedList<int>::create({2, 1}),
                LinkedList<int>::create({3, 1, 2}),
                LinkedList<int>::create({3, 2, 1}),
                LinkedList<int>::create({1, 2, 3}),
                LinkedList<int>::create({10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60})
        };

        for (auto &list: lists) {
            cout << "Processing list: " << list.to_string() << endl;

            obj.sort(list, 0, list.length());
            cout << "Sorted: " << list.to_string() << endl;
            cout<<endl;
        }
    }

    void sort(LinkedList<int> &list, int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            LinkedList<int> first;
            LinkedList<int> second;

            divide(list, l, m, r, first, second);
            sort(first, l, m);
            sort(second, m + 1, r);
            list = merge(first, second);
        }
    }

    void divide(LinkedList<int> &list, int l, int m, int r, LinkedList<int> &first, LinkedList<int> &second) {
        Node *firstRoot = list.get_head();
        Node *secondRoot = list.get_head();
        Node *tmp = firstRoot;
        int sz = 0;
        while (sz < m - l) {
            tmp = tmp->next;
            sz++;
        }
        secondRoot = tmp->next;
        tmp->next = nullptr;

        first = LinkedList<int>(firstRoot);
        second = LinkedList<int>(secondRoot);
    }

    LinkedList<int> merge(LinkedList<int> &first, LinkedList<int> &second) {
        Node *root = new Node(-1);
        Node *rootFirst = first.get_head();
        Node *rootSecond = second.get_head();

        Node *tmp = root;
        int size = 0;
        while (rootFirst && rootSecond) {
            if (rootFirst->val < rootSecond->val) {
                tmp->next = rootFirst;
                rootFirst = rootFirst->next;
            } else {
                tmp->next = rootSecond;
                rootSecond = rootSecond->next;
            }
            size++;
            tmp = tmp->next;
        }
        while (rootFirst) {
            tmp->next = rootFirst;
            tmp = tmp->next;
            rootFirst = rootFirst->next;
            size++;
        }
        while (rootSecond) {
            tmp->next = rootSecond;
            tmp = tmp->next;
            rootSecond = rootSecond->next;
            size++;
        }

        return LinkedList<int>(root->next);
    }
};