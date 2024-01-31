#pragma once
#include "../Header.h"
#include "ds/BinarySearchTree.h"

/*
https://www.careercup.com/question?id=15320677

Given a BST and a value x. Find two nodes in the tree whose sum is equal x. Additional space: O(height of the tree). It is not allowed to modify the tree

solution : having complexity O(n)(time)+O(height of BST)(space)
observation : if we are given a sorted array instead of a BST and the same question was asked then so solve this problem in O(n)+O(1) complexity,
we keep two indexes one at start and 2nd one at end, and apply following algo.

if(A[1st_index] + A[2nd_index] < x)
    2nd_index--;
else if (A[1st_index] + A[2nd_index] > x)
    1st_index++;
else
     print 1st_index,2nd_index;
do this until 2nd_index > 1st_index
*/
class FindTwoNodesWithGivenSumInBST {
    using Node = BinarySearchTree<int, int>::Node;

   public:
    static void test() {
        FindTwoNodesWithGivenSumInBST obj;

        BinarySearchTree<int, int> bst;
        bst.insert(10, 10);
        bst.insert(2, 2);
        bst.insert(3, 3);
        bst.insert(5, 5);
        bst.insert(8, 8);
        bst.insert(9, 9);
        bst.insert(1, 1);

        bst.inorder();

        for (int x = 0; x <= 20; x++) {
            pair<int, int> res = obj.findPairsWithSum(bst.root, x);
            cout << format("Pair with sum={0} is {1}", x, to_string(res)) << endl;
        }
    }

   private:
    pair<int, int> findPairsWithSum(Node *root, int x) {
        stack<Node *> left;
        stack<Node *> right;

        Node *leftNode = root, *rightNode = root;
        bool moveLeft = true, moveRight = true;

        while (true) {
            while (moveLeft && leftNode) {
                left.push(leftNode);
                leftNode = leftNode->left;
            }

            while (moveRight && rightNode) {
                right.push(rightNode);
                rightNode = rightNode->right;
            }

            if ((!leftNode && left.empty()) || (!rightNode && right.empty())) break;
            moveLeft = moveRight = false;

            if (!leftNode) {
                leftNode = left.top();
                left.pop();
            }

            if (!rightNode) {
                rightNode = right.top();
                right.pop();
            }

            if (leftNode->val >= rightNode->val) break;

            if (leftNode->val + rightNode->val == x)
                return {leftNode->val, rightNode->val};
            else if (leftNode->val + rightNode->val < x) {
                moveLeft = true;
                leftNode = leftNode->right;
            } else if (leftNode->val + rightNode->val > x) {
                moveRight = true;
                rightNode = rightNode->left;
            }
        }

        return {-1, -1};
    }
};