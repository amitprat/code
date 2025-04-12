#pragma once
#include "../header.h"
#include "BinaryTree.h"

template <class T>
class BinarySearchTree : public BinaryTree<T> {
   public:
    void insert(T val) {
        this->root = insert(this->root, val);
    }

   private:
    BinaryTree<T>::Node *insert(BinaryTree<T>::Node *root, T val) {
        if (!root) return new BinaryTree<T>::Node(val);

        if (val < root->val) {
            root->left = insert(root->left, val);
        } else if (val > root->val) {
            root->right = insert(root->right, val);
        } else {
            root->val = val;
        }

        return root;
    }

   public:
    static void test() {
        BinarySearchTree<int> bst;
        bst.insert(3);
        bst.insert(1);
        bst.insert(4);
        bst.insert(2);

        cout << "Inorder: " << bst.inorder() << endl;
        cout << "Preorder: " << bst.preorder() << endl;
        cout << "Postorder: " << bst.postorder() << endl;
        cout << "LevelOrder: " << bst.levelOrder() << endl;
    }
};