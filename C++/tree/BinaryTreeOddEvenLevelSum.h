#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=16126663

Given a binary tree. Write a function that takes only root node as arguement and returns (sum of values at odd height)-(sum of values at even height).

Solution with a some simplification:
Call the function with the root of the tree
The root is at height 0.

double sum(Node root){
    if(root == null){
        return 0;
    }

    return -(root.value + sum(root.left) + sum(root.right));
}

      1
    2   3
4           6
*/
class BinaryTreeOddEvenLevelSum {
    using TreeNode = BinaryTree<int>::Node;

   public:
    static void test() {
        BinaryTreeOddEvenLevelSum obj;

        {
            TreeNode* root = new TreeNode(1);
            root->left = new TreeNode(2);
            root->right = new TreeNode(3);
            root->left->left = new TreeNode(4);
            root->right->right = new TreeNode(6);

            auto res1 = obj.sum_inorder(root, -1 /*mul*/);
            auto res2 = obj.sum_preorder(root);
            auto res3 = obj.sum_postorder(root, 0 /*level*/);

            assert(res1 == res2);
            assert(res1 == res3);

            cout << "Sum : " << res1 << endl;
        }

        {
            TreeNode* root = new TreeNode(10);
            root->left = new TreeNode(9);
            root->right = new TreeNode(11);
            root->left->left = new TreeNode(8);
            root->left->right = new TreeNode(9);
            root->right->left = new TreeNode(7);
            root->right->right = new TreeNode(12);

            auto res1 = obj.sum_inorder(root, -1 /*mul*/);
            auto res2 = obj.sum_preorder(root);
            auto res3 = obj.sum_postorder(root, 0 /*level*/);

            assert(res1 == res2);
            assert(res1 == res3);

            cout << "Sum : " << res1 << endl;
        }
    }

   private:
    int sum_preorder(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        return -(root->val + sum_preorder(root->left) + sum_preorder(root->right));
    }

   private:
    int sum_inorder(TreeNode* root, int mul) {
        if (root == nullptr) {
            return 0;
        }

        return sum_inorder(root->left, -mul) + mul * root->val + sum_inorder(root->right, -mul);
    }

   private:
    int sum_postorder(TreeNode* root, int level) {
        if (root == NULL) return 0;

        int left = sum_postorder(root->left, level + 1);
        int right = sum_postorder(root->right, level + 1);

        if (level % 2 == 0)
            return left + right - root->val;
        else
            return left + right + root->val;
    }
};