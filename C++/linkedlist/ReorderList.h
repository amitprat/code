#include "../header.h"

/*
* https://leetcode.com/problems/reorder-list/?envType=problem-list-v2&envId=oizxjoit
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.
*/
class ReorderList {
    struct Node {
        int val;
        Node* next;
        Node(int val) : val(val), next(nullptr) {}
    };

   public:
    static void test() {
        ReorderList obj;
        vector<vector<int>> inputs = {
            {1},
            {1, 2},
            {1, 2, 3},
            {1, 2, 3, 4},
            {1, 2, 3, 4, 5},
            {1, 2, 3, 4, 5, 6},
            {1, 2, 3, 4, 5, 6, 7}};
        for (auto& input : inputs) {
            cout << "Input: " << input << endl;

            Node* head = obj.create(input);
            head = obj.reorderList(head);
            obj.print(head);
        }
    }

   public:
    Node* reorderList(Node* head) {
        auto [first, second] = split(head);
        second = reverse(second);
        first = merge(first, second);

        return first;
    }

   private:
    pair<Node*, Node*> split(Node* head) {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        slow->next = nullptr;

        return {head, fast};
    }

    Node* reverse(Node* head) {
        Node* prev = nullptr;
        while (head) {
            auto next = head->next;
            head->next = prev;
            prev = head;
            head = next;
        }

        return prev;
    }

    Node* merge(Node* first, Node* second) {
        Node* head = first;
        while (first && second) {
            auto firstnext = first->next;
            auto secondnext = second->next;
            first->next = second;
            second->next = firstnext;

            first = firstnext;
            second = secondnext;
        }

        return head;
    }

   private:
    Node* create(const vector<int>& arr) {
        Node* head = new Node(-1);
        Node* tmp = head;
        for (auto& val : arr) {
            tmp->next = new Node(val);
            tmp = tmp->next;
        }
        return head->next;
    }

    void print(Node* head) {
        cout << "List: [";
        while (head) {
            cout << head->val << ", ";
            head = head->next;
        }
        cout << "]" << endl;
    }
};