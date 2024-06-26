#pragma once
#include "../header.h"
/*
Diameter of a tree
Longest of all shorted path in a tree
Longest path between two leaves of tree

int height(tree *root) {
  if(!root) return 0;
  return 1 + max(height(root->left), height(root->right));
}
int diameter(tree *root) {
  if(!root) return 0;
  int lh = height(root->left);
  int rh = height(root->right);

  int ld = diameter(root->left);
  int rd = diameter(root->right);

  return ( max( max(ld,rd) , lh+rh+1) );
}

*/

class DiameterOfBinaryTree {
   public:
    int diameter(BinaryTree<int>::Node *root) {
        if (!root) return 0;

        int lh = height(root->left);
        int rh = height(root->right);

        int ld = diameter(root->left);
        int rd = diameter(root->right);

        return (max(max(ld, rd), lh + rh + 1));
    }

    int height(BinaryTree<int>::Node *root) {
        if (!root) return 0;

        return 1 + max(height(root->left), height(root->right));
    }
};