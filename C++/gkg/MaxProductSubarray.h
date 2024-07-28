#pragma once
#include "../header.h"

class MaxProductSubarray {
   public:
    static void test() {
        vector<int> arr = {1, -2, -3, 0, 7, -8, -2};

        MaxProductSubarray obj;
        cout << "Maximum Sub array product is " << obj.maxSubarrayProduct(arr) << endl;
    }

   public:
    int maxSubarrayProduct(vector<int>& arr) {
        if (arr.size() == 0) return 0;

        int maxSoFar = arr[0];
        int maxEndingHere = arr[0];
        int minEndingHere = arr[0];

        for (int i = 1; i < arr.size(); i++) {
            int curMax = max(max(arr[i] * maxEndingHere, arr[i] * minEndingHere), arr[i]);
            minEndingHere = min(min(arr[i] * maxEndingHere, arr[i] * minEndingHere), arr[i]);

            maxEndingHere = curMax;
            maxSoFar = max(maxSoFar, maxEndingHere);
        }

        return maxSoFar;
    }
};