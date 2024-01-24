#pragma once
#include "../header.h"
#include "LinkedList.h"

class PartitionList
{
public:
    static void test()
    {
        PartitionList obj;
        {
            LinkedList<int> list1;
            int val = 3;
            list1.add(6).add(2).add(7).add(1).add(3).add(5).add(9);
            cout << "List: " << list1.to_string() << ", partition around = " << val << endl;

            Node<int>* second = nullptr;
            Node<int>* first = list1.getRaw();
            obj.partition(first, second, val);
            obj.print(first);
            obj.print(second);
        }
        cout << endl;

        {
            LinkedList<int> list1;
            int val = 1;
            list1.add(6).add(2).add(7).add(1).add(3).add(5).add(9);
            cout << "List: " << list1.to_string() << ", partition around = " << val << endl;

            Node<int>* second = nullptr;
            Node<int>* first = list1.getRaw();
            obj.partition(first, second, val);
            obj.print(first);
            obj.print(second);
        }
        cout << endl;

        {
            LinkedList<int> list1;
            int val = 0;
            list1.add(6).add(2).add(7).add(1).add(3).add(5).add(9);
            cout << "List: " << list1.to_string() << ", partition around = " << val << endl;

            Node<int>* second = nullptr;
            Node<int>* first = list1.getRaw();
            obj.partition(first, second, val);
            obj.print(first);
            obj.print(second);
        }
        cout << endl;

        {
            LinkedList<int> list1;
            int val = 10;
            list1.add(6).add(2).add(7).add(1).add(3).add(5).add(9);
            cout << "List: " << list1.to_string() << ", partition around = " << val << endl;

            Node<int>* second = nullptr;
            Node<int>* first = list1.getRaw();
            obj.partition(first, second, val);
            obj.print(first);
            obj.print(second);
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

    void partition(Node<int>*& first, Node<int>*& second, int val)
    {
        Node<int>* node = first;
        first = nullptr;
        while (node) {
            Node<int>* next = node->next;
            if (node->val <= val) {
                node->next = first;
                first = node;
            }
            else {
                node->next = second;
                second = node;
            }
            node = next;
        }
    }

    void partitionCareerCup(Node<int>*& node, int val)
    {
        Node<int>* head = node;
        Node<int>* tail = node;
        head->next = nullptr;

        while (node) {
            Node<int>* next = node->next;
            if (node->val < val) {
                node->next = head;
                head = node;
            }
            else {
                tail->next = node;
                tail = node;
            }
            node = next;
        }
        tail->next = nullptr;
        node = head;
    }
};