// diameter_binary_tree.h
// Computes the diameter (longest path between any two nodes) of a binary tree.
// Author: Code Copilot
// Date: 2025-04-16

#pragma once
#include "../header.h"

class DiameterOfBinaryTree {
    using Node = BinaryTree<int>::Node;

   public:
    /**
     * Naive recursive solution to find the diameter.
     * Time complexity: O(n^2)
     * @param root The root of the tree.
     * @return The diameter of the tree.
     */
    int diameterNaive(Node* root) {
        if (!root) return 0;

        int lh = height(root->left);
        int rh = height(root->right);

        int ld = diameterNaive(root->left);
        int rd = diameterNaive(root->right);

        return std::max({ld, rd, lh + rh});
    }

    /**
     * Calculates the height of a binary tree.
     * @param root The root of the tree.
     * @return The height of the tree.
     */
    int height(Node* root) {
        if (!root) return 0;
        return 1 + std::max(height(root->left), height(root->right));
    }

   public:
    /**
     * Optimized diameter calculation using post-order traversal.
     * Time complexity: O(n)
     * @param root The root of the tree.
     * @param height Reference to return height.
     * @return The diameter of the tree.
     */
    int diameterOptimized(Node* root, int& height) {
        if (!root) {
            height = 0;
            return 0;
        }

        int lh = 0, rh = 0;
        int ld = diameterOptimized(root->left, lh);
        int rd = diameterOptimized(root->right, rh);

        height = 1 + std::max(lh, rh);
        return std::max({ld, rd, lh + rh});
    }

   public:
    /**
     * Wrapper to calculate diameter using recursion with max height tracking.
     * @param root The root of the tree.
     * @return The diameter of the tree.
     */
    int diameter(Node* root) {
        int result = 0;
        diameterUtil(root, result);
        return result;
    }

    /**
     * Helper recursive function to calculate diameter and height.
     * @param root The root of the tree.
     * @param res Reference to track the max diameter found.
     * @return The height of the tree at root.
     */
    int diameterUtil(Node* root, int& res) {
        if (!root) return 0;

        int lh = diameterUtil(root->left, res);
        int rh = diameterUtil(root->right, res);

        res = std::max(res, lh + rh);
        return 1 + std::max(lh, rh);
    }

   public:
    /**
     * Unit test function to validate different diameter implementations.
     */
    static void test() {
        // Constructed binary tree is
        //          5
        //        /   \
        //       8     6
        //      / \   /
        //     3   7 9
        Node* root = new Node(5);
        root->left = new Node(8);
        root->right = new Node(6);
        root->left->left = new Node(3);
        root->left->right = new Node(7);
        root->right->left = new Node(9);

        DiameterOfBinaryTree solver;

        int naive = solver.diameterNaive(root);
        int height = 0;
        int optimized = solver.diameterOptimized(root, height);
        int efficient = solver.diameter(root);

        assert(naive == 4);  // Path: 4-2-1-3-7
        assert(optimized == 4);
        assert(efficient == 4);

        std::cout << "All diameter calculation methods passed.\n";
    }
};
