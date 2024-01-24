#include "../header.h"

/*
https://careercup.com/question?id=5261732222074880

how to merge two binary search tree into balanced binary search tree.. Let there be m elements in first tree and n elements in the other tree.
Your merge function should take O(m+n) time with in constant space.

This can be done in 3 steps:
1. covert the BSTs to sorted linked list (this can be done in place with O(m+n) time)
2. Merge this two sorted linked lists to a single list (this can be done in place with O(m+n) time)
3. Convert sorted linked list to balanced BST (this can be done in place with O(m+n) time)
*/

class MergeTwoBalancedBST {
   private:
    TreeNode *mergeBst(TreeNode *root1, TreeNode *root2) {
        ListNode *head1, *head2;

        head1 = inorder(root1, head1);
        head2 = inorder(root2, head2);

        ListNode *head = mergeLinkedList(head1, head2);

        TreeNode *root = convertSortedListToBst(head);
    }

    ListNode *inorder(TreeNode *root, ListNode *head) {
        if (!root) return head;

        inorder(root->left, head);
        if (!head)
            head = new ListNode(root->val);
        else {
            head->next = new ListNode(root->val);
            head = head->next;
        }
        inorder(root->right, head);
    }

    ListNode *mergeLinkedList(ListNode *head1, ListNode *head2) {
        if (!head1) return head2;
        if (!head2) return head1;

        if (head1->val <= head2->val) {
            head1->next = mergeLinkedList(head1->next, head2);
            return head1;
        } else {
            head2->next = mergeLinkedList(head1, head2->next);
            return head2;
        }
    }

   private:
    TreeNode *convertSortedListToBst(ListNode *head) {
        if (!head) return nullptr;

        ListNode *first = nullptr, *second = nullptr;
        auto mid = findMid(head, first, second);

        TreeNode *root = new TreeNode(mid->val);
        root->left = convertSortedListToBst(first);
        root->right = convertSortedListToBst(second);

        return root;
    }

    ListNode *findMid(ListNode *head, ListNode *&first, ListNode *&second) {
        if (!head) return nullptr;
        if (!head->next) return head;

        first = head;
        second = head->next;
        ListNode *mid;

        while (second && second->next) {
            mid = first;
            first = first->next;
            second = second->next->next;
        }

        mid = mid->next;
        mid->next = nullptr;
        second = first->next;

        return mid;
    }

   private:
    TreeNode *convertSortedListToBstOptimized(ListNode *head) {
        int n = size(head);

        return convertSortedListToBstOptimized(head, n);
    }

    TreeNode *convertSortedListToBstOptimized(ListNode *&head, int n) {
        if (n == 0) return nullptr;

        auto left = convertSortedListToBstOptimized(head, n / 2);

        TreeNode *root = new TreeNode(head->val);
        head = head->next;

        root->left = left;

        root->right = convertSortedListToBstOptimized(head, n - n / 2 - 1);

        return root;
    }

    int size(ListNode *head) {
        int sz = 0;
        while (head) {
            head = head->next;
            sz++;
        }

        return sz;
    }
};