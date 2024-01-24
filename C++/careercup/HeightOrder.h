#pragma once
#include "../Header.h"

/*
You are given two array, first array contain integer which represent heights of persons and second array contain how many persons in front of him are standing who are greater than him in term of height and forming a queue. Ex
A: 3 2 1
B: 0 1 1
It means in front of person of height 3 there is no person standing, person of height 2 there is one person in front of him who has greater height then he, similar to person of height 1. Your task to arrange them
Ouput should be.
3 1 2
Here - 3 is at front, 1 has 3 in front ,2 has 1 and 3 in front.
*/
class HeightOrder {
    class BinaryTree {
        struct Node {
            int val;
            Node* left, * right;
            int size = 0;
            Node(int val, int size = 1) : val(val), size(size) {
                left = right = nullptr;
            }
        };
        Node* root = nullptr;
    public:
        void insert(int height, int order) {
            root = insert(root, height, order);
        }
        vector<int> inorder() {
            vector<int> result;
            inorder(root, result);

            return result;
        }
    private:
        Node* insert(Node* cur, int height, int order) {
            if (!cur) return new Node(height, order + 1);
            if (order < cur->size) {
                cur->size += 1;
                cur->left = insert(cur->left, height, order);
            }
            else {
                cur->right = insert(cur->right, height, order - cur->size);
            }
            return cur;
        }
        void inorder(Node* cur, vector<int>& result) {
            if (cur) {
                inorder(cur->left, result);
                result.push_back(cur->val);
                inorder(cur->right, result);
            }
        }
    };
public:
    static void test() {
        HeightOrder obj;
        vector<int> heights = { 3,2,1 };
        vector<int> order = { 0,1,1 };

        auto res = obj.getOrder(heights, order);
        cout << to_string(res) << endl;
    }

    vector<int> getOrder(vector<int> heights, vector<int> order) {
        BinaryTree tree;
        for (int i = 0; i < heights.size(); i++) {
            tree.insert(heights[i], order[i]);
        }

        return tree.inorder();
    }
};

/*
This can be solved using rope data structure.
It's like a binary tree except that each node maintains the number of nodes in the left subtree+1 for itself. Whenever a new number is inserted, if the value is smaller than the node's number it goes to the left otherwise right. When it goes to the right, the value of the node is decreased by the value of the branch node.
Ex Nodes: 6 5 4 3 2 1
values: 0 0 0 2 2 4
1. Make 6 as the root of the tree, its value = 1;
2. Insert 5. Value of 5(0) < value of 6(1) so it goes to the left. New value of 6 = 2, value of 5=1;
3. Insert 4, value of 4 < value of 6 so goes to the left; again goes to the left of 5. New values of 4 = 1, value of 5 = 2, value of 6 = 3
4. Insert 3, goes to the left of 6 but to the right of 5. New values 6 = 4, value of 3 = 1, rest unchanged
5. Insert 2, goes to the left of 6, right of 5 (value of 2 is decreased by value of 5 so its now 0), left of 3. New values of 3 = 2, value of 2 = 1, value of 6 = 5
6. Insert 1, goes to the left of 6, right of 5, right of 3.
Do an in-order traversal of tree. It is imperative to insert the nodes in decreasing order
*/