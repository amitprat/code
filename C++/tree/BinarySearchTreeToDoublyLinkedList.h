#pragma once
#include "../Header.h"

/*
Given a Binary Tree (BT), convert it to a Doubly Linked List(DLL) In-Place. The left and right pointers in nodes are to be used as previous and next pointers respectively in converted DLL. The order of nodes in DLL must be same as Inorder of the given Binary Tree. The first node of Inorder traversal (leftmost node in BT) must be the head node of the DLL.

https://leetcode.com/discuss/interview-question/4177029/Binary-Tree-to-DLL/
https://www.geeksforgeeks.org/convert-binary-tree-to-doubly-linked-list-using-inorder-traversal/
*/
namespace bsttodll {
template <class T>
class BST {
   public:
    class Node {
       public:
        T val;
        Node *left, *right;
        Node(T val) : val(val), left(nullptr), right(nullptr) {}
    };
    Node* root = nullptr;

   public:
    void insert(T val) {
        root = insert(root, val);
    }
    string to_string() {
        stringstream ss;
        inorder(root, ss);
        return ss.str();
    }
    Node* getRoot() {
        return root;
    }

   private:
    Node* insert(Node* cur, T val) {
        if (!cur) return new Node(val);

        if (val < cur->val)
            cur->left = insert(cur->left, val);
        else
            cur->right = insert(cur->right, val);

        return cur;
    }
    void inorder(Node* cur, stringstream& ss) {
        if (cur) {
            inorder(cur->left, ss);
            ss << cur->val << " ";
            inorder(cur->right, ss);
        }
    }
};
class BSTToDll {
   public:
    static void test() {
        BSTToDll obj;

        BST<int> bst;
        bst.insert(10);
        bst.insert(5);
        bst.insert(15);
        bst.insert(20);
        bst.insert(30);
        cout << bst.to_string() << endl;

        BST<int>::Node* head = nullptr;
        obj.covertBSTToDLL(bst.getRoot(), head);
        while (head) {
            cout << head->val << " ";
            head = head->right;
        }
    }

   private:
    void covertBSTToDLL(BST<int>::Node* root, BST<int>::Node*& head) {
        if (!root) return;

        static BST<int>::Node* prev = nullptr;
        covertBSTToDLL(root->left, head);
        if (!prev)
            head = root;
        else
            prev->right = root;
        root->left = prev;
        prev = root;
        covertBSTToDLL(root->right, head);
    }

   private:
    BST<int>::Node* covertBSTToDLL2(BST<int>::Node* root) {
        BST<int>::Node* next = nullptr;
        return covertBSTToDLL2(root, next);
    }

    BST<int>::Node* covertBSTToDLL2(BST<int>::Node* root, BST<int>::Node*& next) {
        if (!root) return root;

        covertBSTToDLL(root->right, next);

        root->right = next;
        if (next) next->left = root;
        next = root;

        covertBSTToDLL(root->left, next);

        return next;
    }
};
}  // namespace bsttodll