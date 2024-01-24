#include "../header.h"

/*
https://careercup.com/question?id=22809662

A tree, (NOT NECESSARILY BINARY), has nodes numbered 0 to N-1. An array has indices ranging from 0 to N-1. The indices denote the node ids and values denote the ids of parents. A value of -1 at some index k denotes that node with id k is the root. For ex:


3 3 3 -1 2
0 1 2 3 4
In the above, nodes with ids 0, 1 & 2 have 3 as parent. 3 is the root as its parent = -1 and 2 is the parent of node id 4.

Given such an array, find the height of the tree.

Here's a dynamic programming solution which does this in O(n).


public int countDepth(int[] tree) {
    int[] height = new int[tree.length];
    for (int i = 0; i < tree.length; i++)
        height[i] = -1;
    int maxHeight = -1;
    for (int i = 0; i < tree.length; i++) {
        if (height[i] == -1)
            maxHeight = max(maxHeight, findHeight(i, height, tree));
    }
}

private int findHeight(int i, int[] height, int[] tree) {
    if (height[i] != -1)
        return height[i];
    if (tree[i] == -1) {
        height[i] = 0;
    else
        height[i] = 1 + findHeight(tree[i], height, tree);
    return height[i];
}
*/
class MaxHeightOfATree {
   public:
    int maxHeight(vector<int>& tree) {
        int n = tree.size();
        vector<int> heights(n, -1);

        int mx = 0;
        for (int i = 0; i < n; i++) {
            if (heights[i] == -1)
                mx = max(mx, maxHeight(tree, i, height);)
        }

        return mx;
    }

    int maxHeight(vector<int>& tree, int i, vector<int>& height) {
        if (height[i] != -1) return height[i];
        if (tree[i] == -1) return (height[i] = 0);

        return (height[i] = 1 + maxHeight(tree, tree[i], height));
    }
};