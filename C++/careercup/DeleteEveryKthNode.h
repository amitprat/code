#pragma once
#include "../header.h"
#include "../linkedlist/LinkedList.h"

/*
https://www.careercup.com/question?id=14467673

Given a circular single linked list.Write a program that deletes every kth node until only one node is left.
After kth node is deleted, start the procedure from (k+1)th node.
e.g.list is 1->2->3->4->5->1
k=3
1. You are at 1, delete 3.
List is: 1->2->4->5->1
2. You are at 4, delete 1
List is: 2->4->5->2
3. You are at 2,delete 5
List is: 2->4->2
4. You are at 2, delete 2
List is: 4
Return 4.

How efficient you can do it?
*/
class DeleteEveryKthNode {
    using Node = LinkedList<int>::Node;

   public:
    static void test() {
        Node* root = new Node(1);
        root->next = new Node(2);
        root->next->next = new Node(3);
        root->next->next->next = new Node(4);
        root->next->next->next->next = new Node(5);
        root->next->next->next->next->next = root;

        root = deleteEveryKthNode(root, 3);

        cout << root->val << endl;
    }

    static Node* deleteEveryKthNode(Node* root, int k) {
        Node* prev = root;

        while (true) {
            int curSz = 0;
            for (int i = 1; i < k - 1; i++) {
                root = root->next;
                curSz++;
                if (root == prev && curSz == 1) return root;
            }
            auto next = root->next->next;
            delete root->next;
            root->next = next;

            root = root->next;
            prev = root;
        }

        return nullptr;
    }
};