#pragma once
#include "../header.h"

// https://www.careercup.com/question?id=15886674

// Given an array of 0s and 1s, find out:
// 1. all the subsequences where number of 0s = number of 1s
// 2. max length subsequence where number of 0s = number of 1s

// Update:
// We need to find subarrays, not subsequences. Sorry for the confusion.

// Assuming by subsequence you actually meant _subarray_, an O(n) time algorithm is possible.
// Traverse the array from left to right, and maintain a running sum of number of ones - number of zeroes.
// You also have a hashtable keyed on the running sum, and which contains information regarding the number
// of times that running sum appears, and also the leftmost index for which that sum appears.
// Note: Even though the code uses hashtable below, as Eugene pointed out, since the running_sum is between -n and n,
// we can always use an array, guaranteeing O(1) lookups.
// Using this structure, we can compute the answers for both 1 and 2.
// For instance, to compute the number, we check if the running sum appeared before. If it appeared k times before,
// then we get k new sub-arrays with equal number of zeroes and ones.

// The max length uses the left most such idx.
// Here is sample code in python (with random test cases). The O(n) method is named equal_count.

class LongestSeqOfEqualZerosAndOnes {
   public:
    static void test() {
        int arr[] = {0, 0, 1, 0, 1, 0, 0};
        int n = sizeof(arr) / sizeof(arr[0]);

        longestSeq(arr, n);
    }

    static void longestSeq(int arr[], int n) {
        unordered_map<int, pair<int, int>> map;
        int maxLen = 0;
        int startIndex = -1;
        int totalLen = 0;

        int curSum = 0;
        for (int i = 0; i < n; i++) {
            curSum += (arr[i] == 0) ? -1 : 1;

            if (map.find(curSum) != map.end()) {
                auto curLen = i - map[curSum].first;
                if (curLen > maxLen) {
                    maxLen = curLen;
                    startIndex = map[curSum].first + 1;
                }
                totalLen += map[curSum].second;
                map[curSum].second++;
            } else {
                map[curSum] = {i, 1};
            }
        }

        for (int i = startIndex; i < startIndex + maxLen; i++) cout << arr[i] << " ";
        cout << endl;

        cout << "MaxLen " << maxLen << ", TotalLen " << totalLen << endl;
    }
};