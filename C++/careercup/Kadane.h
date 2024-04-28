#pragma once
#include "../header.h"

/*
Maximum subarray sum
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
Given an array arr[] of size N. The task is to find the sum of the contiguous subarray within a arr[] with the largest sum.
*/

class Kadane {
   public:
    int max_subarray_sum(vector<int>& arr) {
        int sum_so_far = 0;
        int max_sum = 0;

        for (auto& e : arr) {
            sum_so_far += e;

            // this will return max sum so far, including negative sum. (infact the least negative number)
            // if we want to consider 0 as maximum sum in such cases, max it with zero as well or after updating sum_so_far with comparision to zero.
            max_sum = max(max_sum, sum_so_far);

            // if its negative, better to discard all elements so far.
            sum_so_far = max(sum_so_far, 0);
        }

        return max_sum;
    }
};