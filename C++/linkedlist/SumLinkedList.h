#pragma once
#include "../header.h"
#include "LinkedList.h"

class SumLinkedList {
public:
    static void test() {
        SumLinkedList obj;
        LinkedList<int> list1;
        list1.add(6).add(2).add(7).add(1);
        obj.print(list1.getRaw());

        LinkedList<int> list2;
        list2.add(9).add(2).add(9);
        obj.print(list2.getRaw());

        LinkedList<int> res = obj.add(list1, list2);
        cout << "Sum: " << res.to_string() << endl;
    }
    void print(Node<int>* node) {
        cout << "LinkedList: ";
        while (node) {
            cout << node->val;
            node = node->next;
        }
        cout << endl;
    }

    LinkedList<int> add(LinkedList<int>& node1, LinkedList<int>& node2)
    {
        LinkedList<int> root;
        int carry = 0;
        Node<int>* cur = add(node1.getRaw(), node2.getRaw(), carry);
        if (carry) {
            Node<int>* newNode = new Node<int>(carry);
            newNode->next = cur;
            cur = newNode;
        }
        root.setRaw(cur);
        return root;
    }

private:
    Node<int>* add(Node<int>* node1, Node<int>* node2, int& carry)
    {
        if (node1 == nullptr || node2 == nullptr) return nullptr;
        Node<int>* next = add(node1->next, node2->next, carry);
        int curSum = carry + node1->val + node2->val;
        carry = curSum / 10;
        Node<int>* cur = new Node<int>(curSum % 10);
        cur->next = next;
        return cur;
    }
};