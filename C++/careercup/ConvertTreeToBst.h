#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=4863668900593664

Given a binary search tree (BST), write a mehtod that will convert this BST into a doubly linked list that is sorted (ascending or descending order) and returns the first element in this list. You may assume you are given following Node class:


public class Node {
    public Node left, right;
    public String val;
}
Example: The following BST
G
/ \
A T
can be converted into a list
A = G = T

Do it in place! Hnce the memory complexity of your algorithm shoul be O(1).
*/
class ConvertBSTToSortedList
{
public:
    static void test() {
        ITNode* root = new ITNode(5);
        root->left = new ITNode(3);
        root->left->left = new ITNode(2);
        root->left->left->left = new ITNode(1);
        root->right = new ITNode(7);
        root->right->left = new ITNode(6);
        root->right->right = new ITNode(8);
        root->right->right->right = new ITNode(9);
        root->left->right = new ITNode(4);

        ITNode* l = convertToSortedList(root);
        while (l) {
            cout << l->val << ", "; l = l->right;
        }
        cout << endl;
    }

    static ITNode* convertToSortedList(ITNode* root) {
        if (!root) return root;

        static ITNode* next = nullptr;
        convertToSortedList(root->right);

        root->right = next;
        if (next) next->left = root;
        next = root;

        convertToSortedList(root->left);

        return next;
    }
};