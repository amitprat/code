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

        ListNode* root1 = ListNode::create({9, 9, 9, 5, 6, 3});
        ListNode* root2 = ListNode::create({9, 4, 3});

        ListNode* result1 = obj.addLists1(root1, root2);
        ListNode* result2 = obj.addLists2(root1, root2);
        ListNode* result3 = obj.addLists3(root1, root2);

        assert(areEqual(result1, result2));
        assert(areEqual(result1, result3));

        cout<<"Adding list1:"<<root1<< " and "<<root2<<endl;
        cout << "Result: "<<result1 << endl;
    }

   public:
    ListNode* addLists1(ListNode* root1, ListNode* root2) {
        int l1 = ListNode::length(root1);
        int l2 = ListNode::length(root2);
        if (l1 > l2) {
            swap(root1, root2);
            swap(l1, l2);
        }

        // pad list with  zeros.
        root1 = padListWithZeros(root1, l2-l1);

        int carry = 0;
        ListNode* root = addListsOfSameSize(root1, root2, carry);
        
        if (carry) {
            ListNode* newNode = new ListNode(carry);
            newNode->next = root;
            root = newNode;
        }

        return root;
    }

private:
    ListNode* padListWithZeros(ListNode* root, int diff) {
        while (diff--) {
            ListNode* newNode = new ListNode(0);
            newNode->next = root;
            root = newNode;
        }

        return root;
    }

    ListNode* addListsOfSameSize(ListNode* root1, ListNode* root2, int& carry) {
        if (!root1 || !root2) return nullptr;

        auto next = addListsOfSameSize(root1->next, root2->next, carry);
        
        auto val1 = root1->val + root2->val + carry;
        carry = val1 / 10;

        auto cur = new ListNode(val1 % 10);
        cur->next = next;

        return cur;
    }

   public:
    ListNode* addLists2(ListNode* head1, ListNode* head2) {
        int sz1 = ListNode::length(head1);
        int sz2 = ListNode::length(head2);

        int carry = 0;
        ListNode* result = nullptr;
        if (sz1 == sz2) {
            result = addSameSize(head1, head2, carry);
        } else {
            int diff = 0;
            if (sz1 < sz2) {
                swap(head1, head2);
                diff = sz2 - sz1;
            } else
                diff = sz1 - sz2;

            ListNode* larger = head1;
            ListNode* smaller = head2;
            while (diff--) larger = larger->next;

            result = addSameSize(larger, smaller, carry);
            result = addRemaining(head1, larger, result, carry);
        }

        if (carry) {
            ListNode* newHead = new ListNode(carry);
            newHead->next = result;
            result = newHead;
        }

        return result;
    }

private:
    ListNode* addSameSize(ListNode* head1, ListNode* head2, int& carry) {
        if (!head1) return nullptr;  // as both lists are of same size so check on one is ok.

        ListNode* next = addSameSize(head1->next, head2->next, carry);
        
        int rem = (head1->val + head2->val + carry) % 10;
        carry = (head1->val + head2->val + carry) / 10;

        ListNode* curNode = new ListNode(rem);
        curNode->next = next;

        return curNode;
    }

    ListNode* addRemaining(ListNode* larger, ListNode* smaller, ListNode* result, int& carry) {
        if (larger == smaller) return result;

        ListNode* next = addRemaining(larger->next, smaller, result, carry);
        
        int rem = (larger->val + carry) % 10;
        carry = (larger->val + carry) / 10;

        ListNode* newNode = new ListNode(rem);
        newNode->next = next;

        return newNode;
    }

   public:
    ListNode* addLists3(ListNode* head1, ListNode* head2) {
        if (!head1 && !head2) return nullptr;
        int n = ListNode::length(head1);
        int m = ListNode::length(head2);

        if (n < m) {
            swap(head1, head2);
            swap(n, m);
        }

        int carry = 0;
        auto head = addLists3(head1, head2, n - m, carry);

        if (carry) {
            ListNode* newHead = new ListNode(carry);
            newHead->next = head;
            head = newHead;
        }

        return head;
    }

    private:
    ListNode* addLists3(ListNode* head1, ListNode* head2, int diff, int& carry) {
        if (!head1 && !head2) return nullptr;

        auto next = addLists3(head1->next, (diff > 0 ? head2 : head2->next), diff - 1, carry);
        
        int sum = carry + head1->val + (diff > 0 ? 0 : head2->val);
        auto cur = new ListNode(sum % 10);
        carry = sum / 10;

        cur->next = next;

        return cur;
    }
};