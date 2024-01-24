#include "../header.h"

/*
      3                     3                   3
    2   1       -->     1       2     -->     1   2
  4       5               5   4             5       4
*/
/*construct seperate mirror tree*/
class MirrorBinaryTree {
    struct Node {
        int val;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : val(val) {}
    };

   public:
    static void test() {
        MirrorBinaryTree obj;
        Node *root;  // make binary tree
        obj.mirror(root);

        obj.swap_node(root);
    }

   private:
    // by constructing duplicate copy of it.
    Node *mirror(Node *root) {
        if (!root) return NULL;

        Node *newTree = new Node(root->data);
        newTree->left = mirror(root->right);
        newTree->right = mirror(root->left);

        return newTree;
    }

    /*inplace swapping*/
    void swap_node(Node *root) {
        if (!root) return;

        swap(root->left, root->right);

        swap_node(root->left);
        swap_node(root->right);
    }
}