#pragma once
#include "../header.h"

class DetectAndRemoveLoopInLinkedList {
   public:
    static void test() {
        DetectAndRemoveLoopInLinkedList obj;
        LinkedList<int> l({1, 2, 3, 4, 5, 6});
        auto head = l.get_head();
        head->next->next->next->next->next->next = head->next->next;

        cout << "List : ";
        obj.print(head);

        auto newHead = obj.removeLoopInLinkedList(head);
        cout << "List : ";
        obj.print(newHead);
    }

    void print(LinkedList<int>::Node* head) {
        unordered_set<int> s;
        while (head && (s.find(head->val) == s.end())) {
            cout << head->val << " ";
            s.insert(head->val);
            head = head->next;
        }
        if (head) cout << " ~ ";
        cout << endl;
    }

    LinkedList<int>::Node* detectAndRemoveLoop(LinkedList<int>::Node* head) {
        if (!head || !head->next) return head;

        auto slow = head;
        auto fast = head->next;

        while (slow != fast && fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        if (!slow || !fast) {
            cout << "No loop" << endl;
            return head;
        }
        cout << "Loop found at node " << slow->val << endl;

        fast = head;
        while (slow && fast && slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        slow->next = nullptr;

        return head;
    }

   public:
    LinkedList<int>::Node* removeLoopInLinkedList(LinkedList<int>::Node* head) {
        LinkedList<int>::Node* intersection = nullptr;
        bool res = hasLoop(head, intersection);
        if (!res) return head;

        cout << "Loop found at " << intersection->val << endl;
        LinkedList<int>::Node* tmp = head;
        while (tmp && intersection && tmp->next != intersection->next) {
            tmp = tmp->next;
            intersection = intersection->next;
        }

        cout << "Removing loop at prev to loop node " << intersection->val << endl;
        intersection->next = nullptr;

        return head;
    }

    bool hasLoop(LinkedList<int>::Node* head, LinkedList<int>::Node*& intersection) {
        LinkedList<int>::Node *slow = head, *fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                intersection = slow;
                return true;
            }
        }

        return false;
    }
};