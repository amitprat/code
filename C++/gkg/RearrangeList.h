#pragma once
#include "../Header.h"

class RearrangeList {
   public:
    static void test() {
        RearrangeList obj;
        vector<ListNode*> lists = {
            ListNode::create({}),
            ListNode::create({1}),
            ListNode::create({1, 2}),
            ListNode::create({1, 2, 3}),
            ListNode::create({1, 2, 3, 4}),
            ListNode::create({1, 2, 3, 4, 5}),
            ListNode::create({1, 2, 3, 4, 5, 6}),
            ListNode::create({1, 2, 3, 4, 5, 6, 7})};

        for (ListNode* root : lists) {
            cout << "Original List: " << root << endl;
            root = obj.rearrange(root);
            cout << "Rearranged List: " << root << endl;
            cout << endl;
        }
    }

    ListNode* rearrange(ListNode* root) {
        ListNode *first = nullptr, *second = nullptr;
        split(root, first, second);
        if (second == nullptr || first->next == second) return root;

        while (second) {
            auto next = first->next;
            first->next = second;
            second = second->next;
            first->next->next = next;
            first = next;
        }

        return root;
    }

    void split(ListNode* root, ListNode*& first, ListNode*& second) {
        if (!root) return;

        first = root;
        second = root->next;
        while (second && second->next) {
            first = first->next;
            second = second->next->next;
        }

        second = first->next;
        first->next = nullptr;

        first = root;

        cout << "First List After Split: " << first << endl;
        cout << "Second List After Split: " << second << endl;
    }
};