#pragma once
#include "../Header.h"

class AddTwoNumbers {
public:
    static void test() {
        AddTwoNumbers obj;
        {
            LinkedListNode<int>* num1 = new LinkedListNode<int>(9);
            num1->next = new LinkedListNode<int>(9);

            LinkedListNode<int>* num2 = new LinkedListNode<int>(9);
            num1->next = new LinkedListNode<int>(9);
            num1->next->next = new LinkedListNode<int>(9);
            num1->next->next->next = new LinkedListNode<int>(9);

            cout << to_string(num1) + to_string(num2) << " = ";

            auto res = obj.add(num1, num2);

            cout << to_string(res) << endl;
        }

        {
            auto num1 = Construct<int>({});
            auto num2 = Construct<int>({ 9999 });
            auto res = obj.add(num1, num2);
            cout << to_string(num1) << " + " << to_string(num2) << " = " << to_string(res) << endl;
        }

        {
            auto num1 = Construct<int>({ 0,0 });
            auto num2 = Construct<int>({ 9,9,9,9 });
            auto res = obj.add(num1, num2);
            cout << to_string(num1) << " + " << to_string(num2) << " = " << to_string(res) << endl;
        }

        {
            auto num1 = Construct<int>({ 1,0 });
            auto num2 = Construct<int>({ 9,0,8,9 });
            auto res = obj.add(num1, num2);
            cout << to_string(num1) << " + " << to_string(num2) << " = " << to_string(res) << endl;
        }

        {
            auto num1 = Construct<int>({ 1,0,0,0 });
            auto num2 = Construct<int>({ 9,0,8,9 });
            auto res = obj.add(num1, num2);
            cout << to_string(num1) << " + " << to_string(num2) << " = " << to_string(res) << endl;
        }

        {
            auto num1 = Construct<int>({ 1,0,0,0,0,0,0 });
            auto num2 = Construct<int>({ 9,0,8,9 });
            auto res = obj.add(num1, num2);
            cout << to_string(num1) << " + " << to_string(num2) << " = " << to_string(res) << endl;
        }
    }

    LinkedListNode<int>* add(LinkedListNode<int>* num1, LinkedListNode<int>* num2) {
        int l1 = length(num1);
        int l2 = length(num2);

        if (l1 == 0) return num2;
        if (l2 == 0) return num1;

        if (l1 < l2) num1 = padList(num1, l2 - l1, 0);
        else if (l1 > l2)  num2 = padList(num2, l1 - l2, 0);

        int carry = 0;
        auto res = sum(num1, num2, carry);
        if (carry != 0) {
            auto* newFront = new LinkedListNode<int>(carry);
            newFront->next = res;
            res = newFront;
        }

        return res;
    }

    LinkedListNode<int>* padList(LinkedListNode<int>* node, int len, int num) {
        while (len--) {
            auto newNode = new LinkedListNode<int>(num);
            newNode->next = node;
            node = newNode;
        }

        return node;
    }

    LinkedListNode<int>* sum(LinkedListNode<int>* node1, LinkedListNode<int>* node2, int& carry) {
        if (!node1) return node2;
        if (!node2) return node1;

        auto next = sum(node1->next, node2->next, carry);
        int curSum = node1->val + node2->val + carry;
        LinkedListNode<int>* curNode = new LinkedListNode<int>(curSum % 10);
        carry = curSum / 10;

        curNode->next = next;

        return curNode;
    }
};