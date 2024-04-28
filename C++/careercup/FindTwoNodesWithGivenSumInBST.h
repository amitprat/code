#pragma once
#include "../ds/BinarySearchTree.h"
#include "../header.h"

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

    class BinarySearchTreeIterator {
        stack<Node *> st;
        Node *root = nullptr;
        bool leftToRight = true;

       public:
        BinarySearchTreeIterator(Node *root, bool leftToRight = true) {
            this->root = root;
            this->leftToRight = leftToRight;
        }

        bool hasNext() {
            return root || !st.empty();
        }

        Node *next() {
            while (root) {
                st.push(root);
                root = leftToRight ? root->left : root->right;
            }

            root = st.top();
            st.pop();

            auto next = root;
            root = leftToRight ? root->right : root->left;

            return next;
        }
    };

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
            pair<int, int> res1 = obj.findPairsWithSum1(bst.root, x);
            pair<int, int> res2 = obj.findPairsWithSum2(bst.root, x);
            assert(res1 == res2);

            cout << format("Pair with sum={0} is {1}", x, to_string(res1)) << endl;
        }
    }

   private:
    pair<int, int> findPairsWithSum1(Node *root, int x) {
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

   private:
    pair<int, int> findPairsWithSum2(Node *root, int x) {
        BinarySearchTreeIterator bstIter1(root);
        BinarySearchTreeIterator bstIter2(root, false);

        auto left = bstIter1.next();
        auto right = bstIter2.next();

        while (bstIter1.hasNext() && bstIter2.hasNext()) {
            if (left == right) break;

            if (left->key + right->key == x) {
                return {left->key, right->key};
            } else if (left->key + right->key < x) {
                left = bstIter1.next();
            } else {
                right = bstIter2.next();
            }
        }

        return {-1, -1};
    }
};