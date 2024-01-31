#pragma once
#include "../header.h"
/*
https://www.geeksforgeeks.org/longest-sub-array-sum-k/

Given an array of Integers, find the Maximum length subarray with sum equal to zero.
Solved by constructing Prefix sum array for the given array. In prefix sum array, any number repeating more than once,
implies subarray between those indices is 0, so store length of this subarray, check for other repeated values too.
*/
class MaxLengthSubarrayWithGivenSum {
   public:
    int findMaxLen(int a[], int n, int target) {
        int sum = 0;
        int maxlen = 0;
        unordered_map<int, int> map;

        for (int i = 0; i < n; i++) {
            sum += a[i];
            if (a[i] == target || sum == target || map.find(sum) != map.end()) {
                if (a[i] == target) maxlen = max(maxlen, 1);                             // if current itself makes target element, consider it
                if (map.find(sum) != map.end()) maxlen = max(maxlen, i - map[sum] + 1);  // if it is partial sum, consider difference.
                if (sum == 0) maxlen = max(maxlen, i + 1);                               // if it is total sum, consider from starting.
            } else {
                map[sum] = i;
            }
        }

        return maxlen;
    }

   public:
    // finding maxlen subarray with given sum.
    // This approach won’t work for negative numbers
    int maxlen(int a[], int n, int x) {
        int sum = 0;
        int start = 0;
        int maxlen = 0;
        for (int i = start; i <= n; i++) {
            while (sum > x && start < i) {
                sum -= a[start++];
            }
            if (sum == x) {
                cout << "Found subarray with given sum between" << start << "," << i << endl;
                maxlen = max(maxlen, i - start + 1);
            }
            sum += a[i];
        }
        return maxlen;
    }
};