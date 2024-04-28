#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5723406763294720

Add two numbers represented as LinkedList (not LeetCode 445 which uses ListNode)
e.g
inputs: '5'->'6'->'3'
'8'->'4'->'2'
output: '1'->'4'->'0'->'5'
method signature:
LinkedList<Integer> sumList(LinkedList<Integer> l1, LinkedList<Integer> l2)
*/

class AddLinkedLists {
   public:
    static void test() {
        AddLinkedLists obj;

        LinkedList<int>::Node* root1 = LinkedList<int>::create({9, 9, 9, 5, 6, 3});
        LinkedList<int>::Node* root2 = LinkedList<int>::create({9, 4, 3});

        LinkedList<int>::Node* result1 = obj.addLists1(root1, root2);
        LinkedList<int>::Node* result2 = obj.addLists2(root1, root2);
        LinkedList<int>::Node* result3 = obj.addLists3(root1, root2);

        assert(areEqual<int>(result1, result2));
        assert(areEqual<int>(result1, result3));

        cout << "Adding list1:" << root1 << " and " << root2 << endl;
        cout << "Result: " << result1 << endl;
    }

   public:
    LinkedList<int>::Node* addLists1(LinkedList<int>::Node* root1, LinkedList<int>::Node* root2) {
        int l1 = LinkedList<int>::length(root1);
        int l2 = LinkedList<int>::length(root2);
        if (l1 > l2) {
            swap(root1, root2);
            swap(l1, l2);
        }

        // pad list with  zeros.
        root1 = padListWithZeros(root1, l2 - l1);

        int carry = 0;
        LinkedList<int>::Node* root = addListsOfSameSize(root1, root2, carry);

        if (carry) {
            LinkedList<int>::Node* newNode = new LinkedList<int>::Node(carry);
            newNode->next = root;
            root = newNode;
        }

        return root;
    }

   private:
    LinkedList<int>::Node* padListWithZeros(LinkedList<int>::Node* root, int diff) {
        while (diff--) {
            LinkedList<int>::Node* newNode = new LinkedList<int>::Node(0);
            newNode->next = root;
            root = newNode;
        }

        return root;
    }

    LinkedList<int>::Node* addListsOfSameSize(LinkedList<int>::Node* root1, LinkedList<int>::Node* root2, int& carry) {
        if (!root1 || !root2) return nullptr;

        auto next = addListsOfSameSize(root1->next, root2->next, carry);

        auto val1 = root1->val + root2->val + carry;
        carry = val1 / 10;

        auto cur = new LinkedList<int>::Node(val1 % 10);
        cur->next = next;

        return cur;
    }

   public:
    LinkedList<int>::Node* addLists2(LinkedList<int>::Node* head1, LinkedList<int>::Node* head2) {
        int sz1 = LinkedList<int>::length(head1);
        int sz2 = LinkedList<int>::length(head2);

        int carry = 0;
        LinkedList<int>::Node* result = nullptr;
        if (sz1 == sz2) {
            result = addSameSize(head1, head2, carry);
        } else {
            int diff = 0;
            if (sz1 < sz2) {
                swap(head1, head2);
                diff = sz2 - sz1;
            } else
                diff = sz1 - sz2;

            LinkedList<int>::Node* larger = head1;
            LinkedList<int>::Node* smaller = head2;
            while (diff--) larger = larger->next;

            result = addSameSize(larger, smaller, carry);
            result = addRemaining(head1, larger, result, carry);
        }

        if (carry) {
            LinkedList<int>::Node* newHead = new LinkedList<int>::Node(carry);
            newHead->next = result;
            result = newHead;
        }

        return result;
    }

   private:
    LinkedList<int>::Node* addSameSize(LinkedList<int>::Node* head1, LinkedList<int>::Node* head2, int& carry) {
        if (!head1) return nullptr;  // as both lists are of same size so check on one is ok.

        LinkedList<int>::Node* next = addSameSize(head1->next, head2->next, carry);

        int rem = (head1->val + head2->val + carry) % 10;
        carry = (head1->val + head2->val + carry) / 10;

        LinkedList<int>::Node* curNode = new LinkedList<int>::Node(rem);
        curNode->next = next;

        return curNode;
    }

    LinkedList<int>::Node* addRemaining(LinkedList<int>::Node* larger, LinkedList<int>::Node* smaller, LinkedList<int>::Node* result, int& carry) {
        if (larger == smaller) return result;

        LinkedList<int>::Node* next = addRemaining(larger->next, smaller, result, carry);

        int rem = (larger->val + carry) % 10;
        carry = (larger->val + carry) / 10;

        LinkedList<int>::Node* newNode = new LinkedList<int>::Node(rem);
        newNode->next = next;

        return newNode;
    }

   public:
    LinkedList<int>::Node* addLists3(LinkedList<int>::Node* head1, LinkedList<int>::Node* head2) {
        if (!head1 && !head2) return nullptr;
        int n = LinkedList<int>::length(head1);
        int m = LinkedList<int>::length(head2);

        if (n < m) {
            swap(head1, head2);
            swap(n, m);
        }

        int carry = 0;
        auto head = addLists3(head1, head2, n - m, carry);

        if (carry) {
            LinkedList<int>::Node* newHead = new LinkedList<int>::Node(carry);
            newHead->next = head;
            head = newHead;
        }

        return head;
    }

   private:
    LinkedList<int>::Node* addLists3(LinkedList<int>::Node* head1, LinkedList<int>::Node* head2, int diff, int& carry) {
        if (!head1 && !head2) return nullptr;

        auto next = addLists3(head1->next, (diff > 0 ? head2 : head2->next), diff - 1, carry);

        int sum = carry + head1->val + (diff > 0 ? 0 : head2->val);
        auto cur = new LinkedList<int>::Node(sum % 10);
        carry = sum / 10;

        cur->next = next;

        return cur;
    }
};