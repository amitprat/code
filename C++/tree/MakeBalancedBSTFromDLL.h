#pragma once
#include "../ds/BinarySearchTree.h"
#include "../header.h"

class MakeBalancedBSTFromDLL {
    using BST = BinarySearchTree<int, int>;
    using Node = BinarySearchTree<int, int>::Node;

   public:
    static void test() {
        MakeBalancedBSTFromDLL obj;

        BST bst1({{1, 2}, {2, 3}, {2, 3}, {5, 3}, {8, 4}});
        BST bst2({{0, 9}, {1, 4}, {5, 7}, {9, 10}, {11, 4}, {13, 20}});

        cout << "BST1: " << bst1.to_string() << endl;
        cout << "BST2: " << bst2.to_string() << endl;

        BST bst3 = obj.makeBalancedBST(bst1, bst2);
        cout << "BST3: " << bst3.to_string() << endl;
    }

    BST makeBalancedBST(BST bst1, BST bst2) {
        // convert bst to dll
        Node* root1 = nullptr;
        makeDLL(bst1.root, root1);
        cout << "DLL1 : ";
        printDLL(root1);

        // convert bst to dll
        Node* root2 = nullptr;
        makeDLL(bst2.root, root2);
        cout << "DLL2 : ";
        printDLL(root2);

        // merge dlls
        Node* root3 = mergeDLLsRecur(root1, root2);
        cout << "DLL3 : ";
        printDLL(root3);

        // make bst from merged dll.
        Node* root = makeBalancedBST(root3);

        BST newBST;
        newBST.root = root;
        cout << "New BST: " << newBST.to_string() << endl;

        return newBST;
    }

   public:
    void makeDLL(Node* root, Node*& dllRoot) {
        static Node* prev = nullptr;
        if (root) {
            makeDLL(root->left, dllRoot);

            root->left = prev;
            if (!dllRoot) dllRoot = root;
            if (prev) {
                prev->right = root;
            }
            prev = root;

            makeDLL(root->right, dllRoot);
        }
    }

   public:
    Node* mergeDLLsRecur(Node* root1, Node* root2) {
        if (!root1) return root2;
        if (!root2) return root1;

        if (root1->key < root2->key) {
            root1->right = mergeDLLsRecur(root1->right, root2);

            if (root1->right) root1->right->left = root1;

            return root1;
        } else {
            root2->right = mergeDLLsRecur(root1, root2->right);

            if (root2->right) root2->right->left = root2;

            return root2;
        }
    }

    Node* mergeDLLs(Node* root1, Node* root2) {
        Node* dummy = new Node(-1, -1);
        Node* runner = dummy;

        while (root1 && root2) {
            cout << root1->key << " " << root2->key << " " << runner->key << endl;

            if (root1->key < root2->key) {
                auto next = root1->right;
                root1->right = nullptr;
                runner->right = root1;
                root1->left = runner;
                runner = runner->right;
                root1 = next;
            } else {
                auto next = root2->right;
                root2->right = nullptr;
                runner->right = root2;
                root2->left = runner;
                runner = runner->right;
                root2 = next;
            }
        }

        return dummy->right;
    }

    Node* makeBalancedBST(Node* root) {
        int sz = size(root);

        return makeBalancedBST(root, sz);
    }

    Node* makeBalancedBST(Node*& head, int sz) {
        if (sz <= 0) return nullptr;

        auto* left = makeBalancedBST(head->left, sz / 2);

        auto* treeRoot = head;
        treeRoot->left = left;

        head = head->right;

        treeRoot->right = makeBalancedBST(head->right, sz - sz / 2 - 1);

        return treeRoot;
    }

    int size(Node* root) {
        if (!root) return 0;

        return 1 + size(root->left) + size(root->right);
    }

    void printDLL(Node* root) {
        while (root) {
            cout << "{" << root->key << ", " << root->val << "}";
            cout << ", ";
            root = root->right;
        }
        cout << endl;
    }
};