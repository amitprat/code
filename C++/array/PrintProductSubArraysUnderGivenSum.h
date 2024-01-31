#pragma once
#include "../header.h"
using namespace std;

/*
https://leetcode.com/problems/subarray-product-less-than-k/description/

Subarray Product Less Than K

Given an array of integers nums and an integer k, return the number of contiguous subarrays where the product of all
the elements in the subarray is strictly less than k.

Input: nums = [10,5,2,6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are:
[10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6]
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
*/

class PrintProductSubArraysUnderGivenSum {
   public:
    static void test() {
        PrintProductSubArraysUnderGivenSum obj;
        vector<int> v = {2, 3, 5, 7};
        int k = 31;
        auto res = obj.findSubArrays(v, k);
        for (auto i : res) {
            for (auto j : i) {
                cout << j << " ";
            }
            cout << endl;
        }

        cout << "Count = " << obj.countSubArr(v, k) << endl;
    }

    vector<vector<int>> findSubArrays(vector<int> v, int k) {
        vector<vector<int>> result;
        int i = 0;
        int j = 0;
        int cur = 1;
        vector<int> subResult;
        while (j < v.size()) {
            if (cur * v[j] < k) {
                cur *= v[j];
                subResult.push_back(v[j++]);
                result.push_back(subResult);
            } else {
                cur = 1;
                i++;
                j = i;
                subResult.clear();
            }
        }

        return result;
    }

    int countSubArr(vector<int> v, int k) {
        int start = 0;
        int end = 0;
        int prod = 1;
        int cnt = 0;
        while (start <= end && end < v.size()) {
            if (prod * v[end] < k) {
                prod *= v[end];
                cnt += end - start + 1;
                end++;
            } else {
                prod /= v[start++];
            }
        }

        return cnt;
    }
};