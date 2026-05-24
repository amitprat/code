#pragma once
#include "../header.h"

/*
Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:

Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.
*/

class Solution {
   public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> result(nums.size());

        vector<pair<int, int>> elements;
        for (int i = 0; i < nums.size(); i++) {
            elements.push_back({nums[i], i});
        }

        vector<pair<int, int>> tmp(elements.size());
        mergesort(elements, 0, elements.size() - 1, result, tmp);

        return result;
    }

    void mergesort(vector<pair<int, int>>& elements, int l, int r, vector<int>& result, vector<pair<int, int>>& tmp) {
        if (l < r) {
            int m = (l + r) / 2;
            mergesort(elements, l, m, result, tmp);
            mergesort(elements, m + 1, r, result, tmp);
            merge(elements, l, m, r, result, tmp);
        }
    }

    void merge(vector<pair<int, int>>& elements, int l, int m, int r, vector<int>& result,
               vector<pair<int, int>>& tmp) {
        int i = l, j = m + 1;
        int k = l;
        int rightSmall = 0;

        while (i <= m && j <= r) {
            if (elements[i].first <= elements[j].first) {
                result[elements[i].second] += rightSmall;
                tmp[k++] = elements[i++];
            } else {
                tmp[k++] = elements[j++];
                rightSmall++;
            }
        }

        while (i <= m) {
            result[elements[i].second] += rightSmall;
            tmp[k++] = elements[i++];
        }

        while (j <= r) {
            tmp[k++] = elements[j++];
        }

        for (i = l; i <= r; i++) {
            elements[i] = tmp[i];
        }
    }
};