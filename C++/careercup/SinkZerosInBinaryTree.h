#include "../header.h"

/*
https://careercup.com/question?id=5344154741637120

Sink Zero in Binary Tree. Swap zero value of a node with non-zero value of one of its descendants
so that no node with value zero could be parent of node with non-zero.

This can be achieved using post-order traversal -


postOrder(BT r) {
    if(r==null)
    return;

    postOrder(r.left);
    postOrder(r.right);

    if(r.val == 0) {
        if(r.left.val != 0) {
            swap(r.val, r.left.val);
        } else {
            swap(r.right, r.right.val);
        }
    }
}
*/
class SinkZerosInBinaryTree {
   private:
    void sinkZeros(Node *root) {
        if (!root) return;

        sinkZeros(root->left);
        sinkZeros(root->right);

        if (root->val == 0) {
            if (root->left && root->left->val != 0)
                swap(root->val, root->left->val);
            else
                swap(root->val, root->right->val);
        }
    }
};