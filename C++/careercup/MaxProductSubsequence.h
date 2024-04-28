#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=16813665

Given a sequence of non-negative integers find a subsequence of length 3 having maximum product with the numbers of the subsequence
being in ascending order.
Example:
Input: 6 7 8 1 2 3 9 10
Ouput: 8 9 10
*/

class MaxProductSubsequence {
   public:
    static void test() {
        vector<int> arr = {6, 7, 8, 1, 2, 3, 9, 10};
        auto res = findSubsequenceWithMaxProduct(arr);

        cout << format("Maximum product subsequence in arr:{} is {} with product={}",
                       to_string(arr), to_string(res.second), res.first)
             << endl;
    }

   private:
    static pair<int, vector<int>> findSubsequenceWithMaxProduct(vector<int>& arr) {
        int mxProduct = 0;
        vector<int> result;

        for (int i = 1; i < arr.size() - 1; i++) {
            // find the highest element on left which is smaller than current element.
            int leftHighestLower = 0;
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] < arr[i] && arr[j] > leftHighestLower) {
                    leftHighestLower = arr[j];
                }
            }

            // find the highest element on right side which is bigger than current element.
            int rightHighestHigher = 0;
            for (int j = i + 1; j < arr.size(); j--) {
                if (arr[j] > arr[i] && arr[j] > rightHighestHigher) {
                    rightHighestHigher = arr[j];
                }
            }

            // consider the product of these 3 elements
            int curMax = leftHighestLower * arr[i] * rightHighestHigher;

            // if current product is greater than max so far, then update it.
            if (curMax > mxProduct) {
                mxProduct = curMax;
                result = {leftHighestLower, arr[i], rightHighestHigher};
            }
        }

        return {mxProduct, result};
    }
};
