#pragma once
#include "../header.h"
#include "BinarySearchTree.h"

class ReconstructTreeFromPreorder {
    using Node = BinarySearchTree<int>::Node;

   public:
    void reconstruct(list<Node *> pre, Node *&root) {
        stack<Node *> st;
        Node *cur = pre.front();
        pre.pop_front();
        st.push(cur);

        while (!st.empty() && !pre.empty()) {
            if (pre.front() > st.top()) {
                st.push(cur = pre.front());
                pre.pop_front();
            } else {
                Node *tmp = nullptr;
                while (!st.empty() && st.top() < pre.front()) {
                    tmp = st.top();
                    st.pop();
                }
                if (tmp != nullptr) {
                    tmp->right = cur = pre.front();
                    st.push(tmp);
                    pre.pop_front();
                } else {
                    st.push(cur = pre.front());
                    pre.pop_front();
                }
            }
            cout << cur->val << " ";
        }
        cout << endl;

        root = st.top();
        st.pop();
    }

   public:
    static void test() {
        BinarySearchTree<int> bst;
        bst.root = new Node(5);
        bst.root->left = new Node(4);
        bst.root->left->left = new Node(1);
        bst.root->left->left->right = new Node(2);
        bst.root->right = new Node(7);
        bst.root->right->left = new Node(6);
        bst.root->right->right = new Node(8);
        bst.root->right->right->right = new Node(9);

        list<Node *> preOrderArray = bst.preorder_list();
        cout << "Preorder: " << bst.preorder() << endl;

        ReconstructTreeFromPreorder obj;
        BinarySearchTree<int> other;
        obj.reconstruct(preOrderArray, other.root);

        cout << "Preorder: " << other.preorder() << endl;
    }
};