#include "../header.h"

/*
https://careercup.com/question?id=6313112158339072

Given a singly linked list, swap the list items in pairs (reconnect the pointers, not simply swap the values). For example:

Before: A->B->C->D
After: B->A->D->C

While I normally stay away from recursion usage in interview questions, here's a case where it greatly simplifies life.

in python:


def swap_rec(node):
    if not node or not node.next:
        return node
    tmp = node.next
    node.next = swap_rec(tmp.next)
    tmp.next = node
    return tmp
To make it work, you hand it the head node of the linked list. It will do the reversals in pairs as specified, and handles cases such as an odd-length list.

The reason I say recursion saves us time here is because tracking the pointers in a loop can become a pain. In either case, the solution is O(n) runtime
*/
class SwapListPairwise {
    Node *swapNodes(Node *root) {
        if (!root || !root->next) return root;

        Node *next = root->next;
        root->next = swapNodes(next->next);
        next->next = root;

        return next;
    }
};