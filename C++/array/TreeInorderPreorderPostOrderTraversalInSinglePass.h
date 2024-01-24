#include "../Header.h"

/*
Give the inorder,postorder& preorder forms of a tree in a single traversal
*/

void traverse(s) {
    if (s) {
        preorder_queue.add(s);
        traverse(s->left);
        inorder_queue.add(s);
        traverse(s->right);
        postorder_queue(s);
    }
}