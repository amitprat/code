#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=19286747
*
* Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-array is maximum.
* The sub-arrays should not overlap.
eg- [2 -1 -2 1 -4 2 8] ans - (-1 -2 1 -4) (2 8), diff = 16

I gave him o(n^2) algorithm but he was not satisfied. An O(n) solution is possible.
We consider all "split points", i.e. points such that one subarray lies to the left of it, and one to the right, and compute the best for each possible split point.
Dynamic programming works.

Given Array A[1,...n]

Using the standard dynamic programming algorithm, we can compute for a given i, the maximum and minimum sum subarrays in A[1...i] and A[i+1 ... n].
Note that the point between i and i+1 is a split point. This can be done by making two passes once from 1 to n, and other from n to 1 and give us
four arrays with the max and min sub-array sums.
Now given the above four arrays, for split point between i and i+1, we can take the max and min combinations (max from right, min from left and max
from left, min from left), and get the combination which gives the better result.
Once we have the max for each split point, we get the global optimum.
O(n) time, O(n) space.
*/

class MaxDiffContiguousSubarray {
   public:
    static void test() {
        vector<int> arr = {2, -1, -2, 1, -4, 2, 8};
        auto result = getMaxDiffSubarray(arr);

        cout << "Max diff sum: " << result << endl;
    }

    static int getMaxDiffSubarray(vector<int> arr) {
        int n = arr.size();
        vector<int> leftMax(n);
        vector<int> rightMax(n);
        vector<int> leftMin(n);
        vector<int> rightMin(n);

        int maxsofar = INT_MIN, maxendinghere = 0;
        for (int i = 0; i < n; i++) {
            maxendinghere = maxendinghere + arr[i];
            maxsofar = max(maxsofar, maxendinghere);
            maxendinghere = max(maxendinghere, 0);
            leftMax[i] = maxsofar;
        }

        maxsofar = INT_MIN, maxendinghere = 0;
        for (int i = n - 1; i >= 0; i--) {
            maxendinghere = maxendinghere + arr[i];
            maxsofar = max(maxsofar, maxendinghere);
            maxendinghere = max(maxendinghere, 0);
            rightMax[i] = maxsofar;
        }

        int minendinghere = 0, minsofar = INT_MAX;
        for (int i = 0; i < n; i++) {
            minendinghere = minendinghere + arr[i];
            minsofar = min(minsofar, minendinghere);
            minendinghere = min(minendinghere, 0);
            leftMin[i] = minsofar;
        }

        minendinghere = 0, minsofar = INT_MAX;
        for (int i = n - 1; i >= 0; i--) {
            minendinghere = minendinghere + arr[i];
            minsofar = min(minsofar, minendinghere);
            minendinghere = min(minendinghere, 0);
            rightMin[i] = minsofar;
        }

        cout << "leftMax=" << leftMax << endl;
        cout << "leftMin=" << leftMin << endl;
        cout << "rightMax=" << rightMax << endl;
        cout << "rightMin=" << rightMin << endl;

        long globalmax = 0;
        for (int i = 1; i < n; i++) {
            long maxDiff1 = abs(rightMax[i] - leftMin[i - 1]);
            long maxDiff2 = abs(leftMax[i - 1] - rightMin[i]);
            globalmax = max(globalmax, max(maxDiff1, maxDiff2));
        }

        return globalmax;
    }
};