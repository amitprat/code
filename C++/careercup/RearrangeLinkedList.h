#include "../header.h"

class RearrangeLinkedList {
    struct Node {
        int val;
        Node *next = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        RearrangeLinkedList obj;
        Node *head = new Node(1);
        head->next = new Node(2);
        head->next->next = new Node(3);
        head->next->next->next = new Node(4);
        head->next->next->next->next = new Node(5);

        obj.print(head);

        obj.rearrageList2(head);

        obj.print(head);
    }

   private:
    void rearrageList(Node *head) {
        // find the mid and reverse second half of list
        Node *mid = findMid(head);
        Node *second = mid->next;
        mid->next = nullptr;
        second = reverse(second);

        // merge two listw now
        merge(head, second);
    }

    Node *findMid(Node *head) {
        Node *slow = head, *fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    Node *reverse(Node *head) {
        Node *prev = nullptr;
        while (head) {
            auto next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }

    void merge(Node *first, Node *second) {
        while (first && second) {
            auto firstNext = first->next;
            auto secondNext = second->next;

            first->next = second;
            second->next = firstNext;

            first = firstNext;
            second = secondNext;
        }

        if (second) first->next = second;
    }

   private:
    // this won't work. We need to make copy entire list to make it work.
    void rearrageList2(Node *head) {
        Node *tail = head;
        reverse(tail);

        merge2(head, tail);
    }

    void merge2(Node *head, Node *tail) {
        while (head != tail) {
            auto headnext = head->next;
            auto tailnext = tail->next;

            head->next = tail;
            tail->next = headnext;

            head = headnext;
            tail = tailnext;
        }
    }

   private:
    void print(Node *head) {
        while (head) {
            cout << head->val << ",";
            head = head->next;
        }
        cout << endl;
    }
};