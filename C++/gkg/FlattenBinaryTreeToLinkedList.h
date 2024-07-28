#pragma once
#include "../header.h"

class FlattenBinaryTreeToLinkedList {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        FlattenBinaryTreeToLinkedList obj;

        Node *root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(5);
        root->left->left = new Node(3);
        root->left->right = new Node(4);
        root->right->right = new Node(6);

        obj.flatten(root);
        obj.traverse(root);
    }

   public:
    void flattenUsingIterativePreorderTraversal(Node *root) {
        stack<Node *> st;
        st.push(root);

        while (!st.empty()) {
            auto cur = st.top();
            st.pop();

            auto left = cur->left;
            auto right = cur->right;

            if (cur->right) cur->right->left = nullptr;
            if (cur->left) {
                cur->left->right = cur->right;
                cur->left->left = nullptr;
            }
            if (cur->left)
                cur->right = cur->left;
            else
                cur->right = cur->right;
            cur->left = nullptr;

            if (right) st.push(right);
            if (left) st.push(left);
        }
    }

   private:
    void flatten(Node *root) {
        stack<Node *> st;
        preOrder(root, st);

        Node *last = nullptr;
        while (!st.empty()) {
            auto cur = st.top();
            st.pop();
            cur->right = last;
            cur->left = nullptr;
            last = cur;
        }
    }

    void preOrder(Node *root, stack<Node *> &st) {
        if (!root) return;
        st.push(root);
        preOrder(root->left, st);
        preOrder(root->right, st);
    }

   private:
    void flatten1(Node *root) {
        while (root) {
            if (root->left) {
                auto right = root->right;
                root->right = root->left;
                root->left = nullptr;

                Node *next = root->right;
                while (next && next->right) {
                    next = next->right;
                }

                next->right = right;
            }

            root = root->right;
        }
    }

   private:
    void flatten3(Node *root) {
        if (!root) return;
        if (root->left) {
            // flatten the lef tree first
            flatten3(root->left);

            // connect the root->left as root->right and set left pointer as null
            auto right = root->right;
            root->right = root->left;
            root->left = nullptr;

            // find rightmost node in left tree and connect the original right node to its end
            auto *tmp = root->right;
            while (tmp && tmp->right) tmp = tmp->right;
            tmp->right = right;
        }

        // flatten the right node.
        flatten3(root->right);
    }

   private:
    Node *flattenRecursiveLeftToRight(Node *node) {
        if (!node) return node;

        Node *left = flattenRecursiveLeftToRight(node->left);
        Node *right = flattenRecursiveLeftToRight(node->right);

        node->left = nullptr;
        node->right = left;
        getRightMostNode(node)->right = right;

        return node;
    }

    Node *getRightMostNode(Node *node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

   private:
    Node *flattenRecursiveRightToLeft(Node *node) {
        if (!node) return node;

        Node *left = flattenRecursiveRightToLeft(node->right);
        Node *right = flattenRecursiveRightToLeft(node->left);

        if (left) {
            getLeaf(left)->right = right;
            node->right = left;
        } else {
            node->right = right;
        }
        node->left = nullptr;

        return node;
    }

    Node *getLeaf(Node *node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

   private:
    void flattenRecursive(Node *root) {
        Node *prev = nullptr;
        flattenRecursive(root, prev);
    }

    void flattenRecursive(Node *root, Node *&prev) {
        if (root == nullptr) return;

        flattenRecursive(root->right, prev);
        flattenRecursive(root->left, prev);

        root->right = prev;
        root->left = nullptr;
        prev = root;
    }

   private:
    void flattenIterativeUsingStack(Node *root) {
        if (root == nullptr) return;

        stack<Node *> st;
        st.push(root);

        while (!st.empty()) {
            Node *current = st.top();
            st.pop();

            if (current->right) {
                st.push(current->right);
            }
            if (current->left) {
                st.push(current->left);
            }

            if (!st.empty()) {
                current->right = st.top();
            }

            current->left = nullptr;
        }
    }

   private:
    void traverse(Node *head) {
        while (head) {
            cout << head->to_string() << " ";
            head = head->right;
        }
        cout << endl;
    }
};