#pragma once
/*
Given a binary tree. Write a function that takes only root node as arguement and returns (sum of values at odd height)-(sum of values at even height).
*/

/*
Solution with a some simplification:
Call the function with the root of the tree
The root is at height 0.
*/

double sum(Node root) {
    if (root == null) {
        return 0;
    }

    return -(root.value + sum(root.left) + sum(root.right));
}