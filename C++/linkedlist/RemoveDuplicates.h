#pragma once
#include "../header.h"
#include "../design/Set.h"
#include "LinkedList.h"

class RemoveDuplicates {
public:
    static void test() {
        RemoveDuplicates obj;
        {
            LinkedList<int> list;
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }
        {
            LinkedList<int> list;
            list.add(1);
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }
        {
            LinkedList<int> list;
            list.add(1);
            list.add(1);
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }
        {
            LinkedList<int> list;
            list.add(1);
            list.add(1);
            list.add(2);
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }
        {
            LinkedList<int> list;
            list.add(1);
            list.add(2);
            list.add(3);
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }

        {
            LinkedList<int> list;
            list.add(1);
            list.add(2);
            list.add(3);
            list.add(3);
            list.add(3);
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }

        {
            LinkedList<int> list;
            list.add(1);
            list.add(1);
            list.add(2);
            list.add(2);
            list.add(3);
            list.add(3);
            cout << "List:" << list.to_string() << endl;

            obj.removeDups2(list);
            cout << "List:" << list.to_string() << endl;
        }
    }

    // keep no copy of duplicates
    void removeDups(LinkedList<int>& list) {
        Node<int>* head = list.getRaw();

        Node<int>* newHead = new Node<int>(-1);
        newHead->next = head;
        Node<int>* tmp = newHead;
        while (tmp->next) {
            if (tmp->next->next && tmp->next->val == tmp->next->next->val) {
                int curVal = tmp->next->val;
                while (tmp->next && tmp->next->val == curVal) {
                    tmp->next = tmp->next->next;
                }
            }
            else {
                tmp = tmp->next;
            }
        }
        list.setRaw(newHead->next);
    }


    void removeDups2(LinkedList<int>& list) {
        Node<int>* cur = list.getRaw();
        Node<int>* prev = new Node<int>(-1);
        Node<int>* newHead = prev;
        while (cur) {
            int curVal = cur->val;
            do {
                prev->next = cur;
                cur = cur->next;
            } while (cur && cur->val == curVal);
            if (curVal == prev->next->val) prev->next = cur;
            prev = prev->next;
        }
        list.setRaw(newHead->next);
    }

    // keep only one copy of duplicates
    void removeDups3(LinkedList<int>& list) {
        auto* head = list.getRaw();
        auto* newHead = head;
        auto* tmp = newHead;
        while (newHead) {
            auto next = newHead->next;
            while (next && newHead->val == next->val) {
                newHead = next;
                next = next->next;

            }
            newHead = newHead->next;
        }
        list.setRaw(tmp);
    }

    // keep only one copy of duplicates
    void removeDups4(LinkedList<int>& list) {
        if (list.empty()) return;
        Set<int> set;
        auto* head = list.getRaw();
        auto* newHead = head;
        auto* tmp = newHead;
        set.add(tmp->val);
        while (tmp->next) {
            if (set.exists(tmp->next->val)) tmp->next = tmp->next->next;
            else set.add(tmp->val);
            tmp = tmp->next;
        }
        list.setRaw(newHead);
    }
};