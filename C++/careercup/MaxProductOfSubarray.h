#pragma once
#include "../Header.h"

class MaxProductOfSubarray {
   public:
    static void test() {
        MaxProductOfSubarray obj;
        vector<vector<int>> inputs = {{6, -3, -10, 0, 2}, {2, 3, 4, 5, -1, 0}};

        for (auto& arr : inputs) {
            auto val1 = obj.maxProduct1(arr);
            auto val2 = obj.maxProduct2(arr);
            auto val3 = obj.maxProduct3(arr);

            assert(val1 == val2);
            cout << "Max product subarray is " << val1 << endl;
        }
    }

   private:
    int maxProduct1(vector<int>& arr) {
        // store the result that is the max we have found so far
        int maxsofar = arr[0];

        // imax/imin stores the max/min product of
        // subarray that ends with the current number A[i]
        for (int i = 1, imax = maxsofar, imin = maxsofar; i < arr.size(); i++) {
            // multiplied by a negative makes big number smaller, small number bigger
            // so we redefine the extremums by swapping them
            if (arr[i] < 0) swap(imax, imin);

            // max/min product for the current number is either the current number itself
            // or the max/min by the previous number times the current one
            imax = max(arr[i], imax * arr[i]);
            imin = min(arr[i], imin * arr[i]);

            // the newly computed max value is a candidate for our global result
            maxsofar = max(maxsofar, imax);
        }

        return maxsofar;
    }

    int maxProduct2(vector<int>& arr) {
        int maxSoFar = 1;
        int maxEndingHere = 1;
        int minEndingHere = 1;

        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] > 0) {
                maxEndingHere *= arr[i];
                minEndingHere = min(minEndingHere * arr[i], 1);
            } else if (arr[i] == 0) {
                maxEndingHere = minEndingHere = 1;
            } else {
                int tmp = maxEndingHere;
                maxEndingHere = max(minEndingHere * arr[i], 1);
                minEndingHere = tmp * arr[i];
            }
            if (maxEndingHere > maxSoFar)
                maxSoFar = maxEndingHere;
        }

        return maxSoFar;
    }

    int maxProduct3(vector<int>& arr) {
        int prod = INT_MIN;
        int mn = 1, mx = 1;

        for (int i = 0; i < arr.size(); i++) {
            int p1 = mn * arr[i];
            int p2 = mx * arr[i];

            mn = min(p1, p2);
            mx = max(p1, p2);

            // update prod
            prod = max(prod, max(mn, mx));

            // reset mn/mx to 1 if needed.
            mn = min(mn, 1);
            mx = max(mx, 1);
        }

        return prod;
    }
};