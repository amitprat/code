#pragma once
#include "../header.h"

/*
Given a Binary Tree and a key, write a function that prints all the ancestors of the key in the given binary tree.

For example, if the given tree is following Binary Tree and the key is 7, then your function should print 4, 2, and 1.
              1
            /   \
          2      3
        /  \
      4     5
     /
    7
*/

class AncestorOfGivenBinaryTree {
    using Node = BinaryTree<int>::Node;

   public:
    static void test() {
        AncestorOfGivenBinaryTree obj;

        Node* root = new Node(1);
        root->left = new Node(2);
        root->right = new Node(3);
        root->left->left = new Node(4);        // FIX: was right, breaking the diagram
        root->left->right = new Node(5);       // FIX: was right->left (wrong subtree)
        root->left->left->left = new Node(7);  // FIX: node 7 was never added

        for (int i = 1; i <= 10; i++) {
            std::println("Ancestors of key={}:", i);  // C++26: std::println replaces cout+endl
            obj.printAncestors2(root, i);
            std::println("");
        }
    }

    // Recursive – uses return value to signal "key found in my subtree"
    // and prints the current node as an ancestor on the way back up
    [[nodiscard]] bool lca(Node* root, int key) {
        if (!root) return false;
        if (root->val == key) return true;

        if (lca(root->left, key) || lca(root->right, key)) {
            std::print("{} ", root->val);
            return true;
        }
        return false;
    }

    // Cleaner recursive variant (same idea as lca, kept for comparison)
    [[nodiscard]] bool printAncestors(Node* root, int key) {
        if (!root) return false;
        if (root->val == key) return true;

        if (printAncestors(root->left, key) || printAncestors(root->right, key)) {
            std::print("{} ", root->val);
            return true;
        }
        return false;  // FIX: was `return left || right;` — undeclared identifiers
    }

    // Iterative via postorder traversal:
    // During a postorder walk, when we reach the target node the stack holds
    // exactly its ancestors (root → … → parent). Pop the key itself, then
    // drain the stack to print them.
    void printAncestors2(Node* root, int key) {
        if (!root) return;

        std::stack<Node*> st;
        Node* lastVisited = nullptr;

        while (root || !st.empty()) {
            // Walk as far left as possible, pushing every node
            while (root) {
                st.push(root);
                root = root->left;
            }

            Node* top = st.top();

            if (top->val == key) {
                // Stack = [root_ancestor … parent_of_key  key]
                //                                          ^^^  st.top()
                st.pop();  // discard the key itself
                while (!st.empty()) {
                    std::print("{} ", st.top()->val);
                    st.pop();
                }
                return;
            }

            // Can we go right? Only if the right child exists AND
            // we haven't just returned from it (lastVisited check prevents
            // infinite loops on nodes with right children).
            if (top->right == nullptr || top->right == lastVisited) {
                lastVisited = top;
                st.pop();  // fully processed — not an ancestor of anything left to find
            } else {
                root = top->right;
            }
        }
        // Key not found in tree — print nothing
    }
};