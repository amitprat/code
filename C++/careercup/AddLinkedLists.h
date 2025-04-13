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

        LinkedList<int> list1({9, 9, 9, 5, 6, 3});
        LinkedList<int> list2({9, 4, 3});

        auto result1 = obj.addLists1(list1.getHead(), list2.getHead());
        auto result2 = obj.addLists2(list1.getHead(), list2.getHead());
        auto result3 = obj.addLists3(list1.getHead(), list2.getHead());

        assert(areEqual<int>(result1, result2));
        assert(areEqual<int>(result1, result3));

        cout << "Adding list1:" << list1 << " and " << list2 << endl;
        cout << "Result: " << LinkedList<int>::to_string(result1) << endl;

        std::cout << "Adding lists completed successfully.\n";
    }

   public:
    [[nodiscard]] LinkedList<int>::Node* addLists1(LinkedList<int>::Node* l1, LinkedList<int>::Node* l2) {
        int len1 = LinkedList<int>::length(l1);
        int len2 = LinkedList<int>::length(l2);
        if (len1 > len2) {
            std::swap(l1, l2);
            std::swap(len1, len2);
        }

        l1 = padListWithZeros(l1, len2 - len1);
        int carry = 0;
        auto result = addListsOfSameSize(l1, l2, carry);

        if (carry) {
            auto newNode = new LinkedList<int>::Node(carry);
            newNode->next = result;
            result = newNode;
        }

        return result;
    }

   private:
    [[nodiscard]] LinkedList<int>::Node* padListWithZeros(LinkedList<int>::Node* head, int count) {
        while (count--) {
            auto newNode = new LinkedList<int>::Node(0);
            newNode->next = head;
            head = newNode;
        }
        return head;
    }

    [[nodiscard]] LinkedList<int>::Node* addListsOfSameSize(LinkedList<int>::Node* n1, LinkedList<int>::Node* n2, int& carry) {
        if (!n1) return nullptr;

        auto next = addListsOfSameSize(n1->next, n2->next, carry);
        int sum = n1->val + n2->val + carry;
        carry = sum / 10;

        auto node = new LinkedList<int>::Node(sum % 10);
        node->next = next;

        return node;
    }

   public:
    [[nodiscard]] LinkedList<int>::Node* addLists2(LinkedList<int>::Node* h1, LinkedList<int>::Node* h2) {
        int len1 = LinkedList<int>::length(h1);
        int len2 = LinkedList<int>::length(h2);

        if (len1 < len2) {
            std::swap(h1, h2);
            std::swap(len1, len2);
        }

        int carry = 0;
        auto result = addLists2Helper(h1, h2, len1 - len2, carry);

        if (carry) {
            auto newNode = new LinkedList<int>::Node(carry);
            newNode->next = result;
            result = newNode;
        }

        return result;
    }

   private:
    [[nodiscard]] LinkedList<int>::Node* addLists2Helper(LinkedList<int>::Node* longer, LinkedList<int>::Node* shorter, int diff, int& carry) {
        if (!longer) return nullptr;

        LinkedList<int>::Node* next;
        int sum = 0;

        if (diff > 0) {
            next = addLists2Helper(longer->next, shorter, diff - 1, carry);
            sum = carry + longer->val;
        } else {
            next = addLists2Helper(longer->next, shorter->next, 0, carry);
            sum = carry + longer->val + shorter->val;
        }

        carry = sum / 10;
        auto node = new LinkedList<int>::Node(sum % 10);
        node->next = next;
        return node;
    }

   public:
    [[nodiscard]] LinkedList<int>::Node* addLists3(LinkedList<int>::Node* h1, LinkedList<int>::Node* h2) {
        int len1 = LinkedList<int>::length(h1);
        int len2 = LinkedList<int>::length(h2);

        if (len1 < len2) {
            std::swap(h1, h2);
            std::swap(len1, len2);
        }

        int carry = 0;
        auto result = addLists3Helper(h1, h2, len1 - len2, carry);

        if (carry) {
            auto newNode = new LinkedList<int>::Node(carry);
            newNode->next = result;
            result = newNode;
        }

        return result;
    }

   private:
    [[nodiscard]] LinkedList<int>::Node* addLists3Helper(LinkedList<int>::Node* h1, LinkedList<int>::Node* h2, int diff, int& carry) {
        if (!h1) return nullptr;

        auto next = addLists3Helper(h1->next, diff > 0 ? h2 : h2->next, diff - 1, carry);
        int sum = carry + h1->val + (diff > 0 ? 0 : h2->val);

        carry = sum / 10;
        auto node = new LinkedList<int>::Node(sum % 10);
        node->next = next;
        return node;
    }
};