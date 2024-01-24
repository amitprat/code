#pragma once
#include "../Header.h"

class RemoveLoop {
public:
    static void test() {
        RemoveLoop obj;
        LinkedListNode<int>* head = new LinkedListNode<int>(1);
        head->next = new LinkedListNode<int>(2);
        head->next->next = new LinkedListNode<int>(3);
        head->next->next->next = new LinkedListNode<int>(4);
        head->next->next->next->next = new LinkedListNode<int>(5);
        head->next->next->next->next->next = new LinkedListNode<int>(6);
        head->next->next->next->next->next->next = head->next->next;

        cout << "List : ";
        obj.print(head);

        auto newHead = obj.removeLoopInLinkedList(head);
        cout << "List : ";
        obj.print(newHead);
    }

    void print(LinkedListNode<int>* head) {
        unordered_set<int> s;
        while (head && (s.find(head->val) == s.end())) {
            cout << head->val << " ";
            s.insert(head->val);
            head = head->next;
        }
        if (head) cout << " ~ ";
        cout << endl;
    }

    LinkedListNode<int>* removeLoop(LinkedListNode<int>* node) {
        if (!node || !node->next) return node;
        auto slow = node;
        auto fast = node->next;

        while (slow != fast && fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        if (!slow || !fast) {
            cout << "No loop" << endl;
            return node;
        }
        cout << "Loop found at node " << slow->val << endl;

        LinkedListNode<int>* prev = nullptr;
        slow = slow->next;
        auto tmp = node;
        while (tmp && slow && (tmp != slow)) {
            tmp = tmp->next;
            prev = slow;
            slow = slow->next;
        }
        prev->next = nullptr;

        return node;
    }

    LinkedListNode<int>* removeLoopInLinkedList(LinkedListNode<int>* head)
    {
        LinkedListNode<int>* intersection = nullptr;
        bool res = hasLoop(head, intersection);
        if (!res) return head;

        cout << "Loop found at " << intersection->val << endl;
        LinkedListNode<int>* tmp = head;
        while (tmp && intersection && tmp->next != intersection->next) {
            tmp = tmp->next;
            intersection = intersection->next;
        }

        cout << "Removing loop at prev to loop node " << intersection->val << endl;
        intersection->next = nullptr;

        return head;
    }

    bool hasLoop(LinkedListNode<int>* head, LinkedListNode<int>*& intersection) {
        LinkedListNode<int>* slow = head, * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) { intersection = slow; return true; }
        }

        return false;
    }
};