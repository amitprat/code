#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=15320677

Given a BST and a value x. Find two nodes in the tree whose sum is equal x. Additional space: O(height of the tree). It is not allowed to modify the tree

solution : having complexity O(n)(time)+O(height of BST)(space)
observation : if we are given a sorted array instead of a BST and the same question was asked then so solve this problem in O(n)+O(1) complexity, we keep two indexes one at start and 2nd one at end, and apply following algo.


if(A[1st_index] + A[2nd_index] < x)
    2nd_index--;
else if (A[1st_index] + A[2nd_index] > x)
    1st_index++;
else
     print 1st_index,2nd_index;
do this until 2nd_index > 1st_index
*/
class FindTwoNodesWithGivenSumInBST
{
    class BST {
    public:
        struct Node {
            int val;
            Node* left, * right;
            Node(int val) :val(val), left(nullptr), right(nullptr) {}
        };

        Node* root = nullptr;

        void insert(int val) {
            root = insert(root, val);
        }

        void inorder() {
            cout << "Inorder: ";
            inorder(root);
            cout << endl;
        }

        pair<int, int> findPairsWithSum(int x) {
            stack<Node*> left;
            stack<Node*> right;

            Node* leftNode = root, * rightNode = root;
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
                if (!leftNode) { leftNode = left.top(); left.pop(); }
                if (!rightNode) { rightNode = right.top(); right.pop(); }

                if (leftNode->val >= rightNode->val) break;
                if (leftNode->val + rightNode->val == x) return { leftNode->val, rightNode->val };
                else if (leftNode->val + rightNode->val < x) { moveLeft = true; leftNode = leftNode->right; }
                else if (leftNode->val + rightNode->val > x) { moveRight = true; rightNode = rightNode->left; }
            }

            return { -1,-1 };
        }

    private:
        Node* insert(Node* node, int val) {
            if (!node) node = new Node(val);

            if (val < node->val) node->left = insert(node->left, val);
            else if (val > node->val) node->right = insert(node->right, val);

            return node;
        }

        void inorder(Node* node) {
            if (!node) return;

            inorder(node->left);
            cout << node->val << " ";
            inorder(node->right);
        }
    };
public:
    static void test() {
        BST bst;
        bst.insert(10);
        bst.insert(2);
        bst.insert(3);
        bst.insert(5);
        bst.insert(8);
        bst.insert(9);
        bst.insert(1);

        bst.inorder();

        for (int x = 0; x <= 20; x++) {
            pair<int, int> res = bst.findPairsWithSum(x);
            cout << x << " = " << to_string(res) << endl;
        }
    }
};