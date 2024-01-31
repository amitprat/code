#pragma once
#include "../header.h"

class FindPredecessorSuccessorOfAllTreeNode {
   public:
    static void test() {
        FindPredecessorSuccessorOfAllTreeNode obj;

        Node *root = new Node(4);
        root->left = new Node(2);
        root->left->left = new Node(1);
        root->left->right = new Node(3);
        root->right = new Node(6);
        root->right->left = new Node(5);
        root->right->right = new Node(7);

        cout << "Successors:" << endl;
        Node *suc = nullptr;
        obj.fillSuccessor(root, suc);
        cout << endl;

        cout << "Inorder:" << endl;
        obj.inorder(root);
        cout << endl;

        cout << "Predecessors:" << endl;
        Node *pred = nullptr;
        obj.fillPredecessor(root, pred);
        cout << endl;

        cout << "Inorder:" << endl;
        obj.inorder(root);
        cout << endl;

        cout << "Print successors:" << endl;
        cout << "Successor of 0 ->" << obj.successor(root, 0) << endl;
        cout << "Successor of 1 ->" << obj.successor(root, 1) << endl;
        cout << "Successor of 2 ->" << obj.successor(root, 2) << endl;
        cout << "Successor of 3 ->" << obj.successor(root, 3) << endl;
        cout << "Successor of 4 ->" << obj.successor(root, 4) << endl;
        cout << "Successor of 5 ->" << obj.successor(root, 5) << endl;
        cout << "Successor of 6 ->" << obj.successor(root, 6) << endl;
        cout << endl;

        cout << "Print predecessors:" << endl;
        cout << "Predecessor of 0 ->" << obj.predecessor(root, 0) << endl;
        cout << "Predecessor of 1 ->" << obj.predecessor(root, 1) << endl;
        cout << "Predecessor of 2 ->" << obj.predecessor(root, 2) << endl;
        cout << "Predecessor of 3 ->" << obj.predecessor(root, 3) << endl;
        cout << "Predecessor of 4 ->" << obj.predecessor(root, 4) << endl;
        cout << "Predecessor of 5 ->" << obj.predecessor(root, 5) << endl;
        cout << "Predecessor of 6 ->" << obj.predecessor(root, 6) << endl;
        cout << endl;
    }

   private:
    struct Node {
        int val;
        Node *left, *right;
        Node *predecessor = nullptr;
        Node *successor = nullptr;

        Node(int val) : val(val), left(nullptr), right(nullptr) {}
    };

   private:
    int successor(Node *root, int val) {
        Node *result = nullptr;

        successor(root, val, result);
        if (result != nullptr) return result->val;

        return -1;
    }

    void successor(Node *root, int val, Node *&suc) {
        if (!root) return;

        if (root->val == val) {
            if (root->right) suc = min(root->right);
            return;
        }

        if (val > root->val) {
            successor(root->right, val, suc);
        } else {
            suc = root;
            successor(root->left, val, suc);
        }
    }

   private:
    int predecessor(Node *root, int val) {
        Node *result = nullptr;

        predecessor(root, val, result);
        if (result != nullptr) return result->val;

        return -1;
    }

    void predecessor(Node *root, int val, Node *&pred) {
        if (!root) return;

        if (root->val == val) {
            if (root->left) pred = max(root->left);
            return;
        }

        if (val > root->val) {
            pred = root;
            predecessor(root->right, val, pred);
        } else {
            predecessor(root->left, val, pred);
        }
    }

   private:
    void fillSuccessor(Node *root, Node *&successor) {
        if (!root) return;

        fillSuccessor(root->right, successor);

        root->successor = successor;
        successor = root;

        fillSuccessor(root->left, successor);
    }

    void fillPredecessor(Node *root, Node *&predecessor) {
        if (!root) return;

        fillPredecessor(root->left, predecessor);

        root->predecessor = predecessor;
        predecessor = root;

        fillPredecessor(root->right, predecessor);
    }

   private:
    void inorder(Node *root) {
        if (!root) return;

        inorder(root->left);

        cout << std::format("Predecessor={}, Val={}, Successor={}",
                            (root->predecessor ? root->predecessor->val : -1),
                            root->val,
                            (root->successor ? root->successor->val : -1))
             << endl;

        inorder(root->right);
    }

    Node *min(Node *root) {
        if (!root) return root;

        while (root->left) root = root->left;

        return root;
    }

    Node *max(Node *root) {
        if (!root) return root;

        while (root->right) root = root->right;

        return root;
    }
};