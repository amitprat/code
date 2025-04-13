/*
      3                     3                   3
    2   1       -->     1       2     -->     1   2
  4       5               5   4             5       4
*/
/*construct seperate mirror tree*/

#pragma once
#include "../header.h"

class MirrorBinaryTree {
    struct Node {
        int val;
        Node* left;
        Node* right;

        explicit Node(int value) : val(value), left(nullptr), right(nullptr) {}
    };

   public:
    /**
     * Entry point to test mirror creation and in-place mirroring.
     */
    static void test() {
        MirrorBinaryTree tree;

        Node* root = new Node(3);
        root->left = new Node(2);
        root->right = new Node(1);
        root->left->left = new Node(4);
        root->right->right = new Node(5);

        Node* mirroredRoot = tree.createMirror(root);
        tree.printTree(mirroredRoot);
        std::cout << "\n";

        tree.inplaceMirror(root);
        tree.printTree(root);
        std::cout << "\n";
    }

    /**
     * Creates a new mirrored binary tree from the original.
     * @param root The root of the original tree.
     * @return The root of the new mirrored tree.
     */
    Node* createMirror(Node* root) {
        if (!root) return nullptr;

        Node* mirrored = new Node(root->val);
        mirrored->left = createMirror(root->right);
        mirrored->right = createMirror(root->left);

        return mirrored;
    }

    /**
     * Converts the binary tree into its mirror in place.
     * @param root The root of the binary tree to be mirrored.
     */
    void inplaceMirror(Node* root) {
        if (!root) return;

        std::swap(root->left, root->right);
        inplaceMirror(root->left);
        inplaceMirror(root->right);
    }

    /**
     * Checks whether two binary trees are mirrors of each other.
     * @param node1 The root of the first tree.
     * @param node2 The root of the second tree.
     * @return True if the trees are mirrors, false otherwise.
     */
    bool areMirrors(Node* node1, Node* node2) {
        if (!node1 && !node2) return true;
        if (!node1 || !node2) return false;

        return node1->val == node2->val &&
               areMirrors(node1->left, node2->right) &&
               areMirrors(node1->right, node2->left);
    }

    /**
     * Prints the binary tree in pre-order traversal.
     * @param node The root node of the tree.
     */
    void printTree(Node* node) {
        if (!node) return;

        std::cout << node->val << " ";
        printTree(node->left);
        printTree(node->right);
    }
};
