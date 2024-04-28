#pragma once
#include "../header.h"
/*
https://www.careercup.com/question?id=22809662
A tree, (NOT NECESSARILY BINARY), has nodes numbered 0 to N-1. An array has indices ranging from 0 to N-1.
The indices denote the node ids and values denote the ids of parents. A value of -1 at some index k denotes that node with id k is the root.
For ex:
3 3 3 -1 2
0 1 2 3 4
In the above, nodes with ids 0, 1 & 2 have 3 as parent. 3 is the root as its parent = -1 and 2 is the parent of node id 4.
Given such an array, find the height of the tree.
*/

class FindTreeHeightFromParentArray {
   public:
    static int findTreeHeight() {
        vector<int> nodes = {3, 3, 3, -1, 2};

        int h1 = findTreeHeight(nodes, -1);
        int h2 = countDepth(nodes);

        assert(h1 == h2);

        return h1;
    }

   private:
    static int findTreeHeight(vector<int>& nodes, int parent) {
        int mxDepth = 0;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i] == parent) {
                int depth = 1 + findTreeHeight(nodes, i);
                mxDepth = max(mxDepth, depth);
            }
        }

        return mxDepth;
    }

   private:
    static int countDepth(vector<int>& nodes) {
        vector<int> height(nodes.size(), -1);

        int mxHeight = -1;
        for (int i = 0; i < nodes.size(); i++) {
            if (height[i] == -1) {
                mxHeight = max(mxHeight, countDepth(i, nodes, height));
            }
        }

        return mxHeight;
    }

    static int countDepth(int parent, vector<int>& nodes, vector<int>& height) {
        if (height[parent] != -1) return height[parent];

        if (nodes[parent] == -1) {
            height[parent] = 0;
        } else {
            height[parent] = 1 + countDepth(nodes[parent], nodes, height);
        }

        return height[parent];
    }
};