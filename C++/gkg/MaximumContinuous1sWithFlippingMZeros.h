#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5106425965576192

You are given with an array of 1s and 0s. And you are given with an integer m, which signifies number of flips allowed.
find the position of zeros which when flipped will produce maximum continuous series of 1s.

e.g.
input:
arr={1 1 0 1 1 0 0 1 1 1 } m=1
output={1 1 1 1 1 0 0 1 1 1} position=2

arr={1 1 0 1 1 0 0 1 1 1 } m=2
output={1 1 0 1 1 1 1 1 1 1} position=5,6

I would use SLIDING WINDOW for this problem. (Just realized that I have used it at least 3 times at careercup!)
Lets use a window covering from index wL to index wR. Let the number of zeros inside the window be nZero.
We try to maintain the window with at most m zeros inside.

The main steps are:
- While nZero is no more than m: expand the window to the right (wR++) and update the count nZero;
- While nZero exceeds m, shrink the window from left (wL++), update nZero;
- Update the widest window along the way. The positions of must-flip zeros are inside the best window.

This solution assumes we can use m or less number of flips.
Time complexity = O(n), space = O(1).
*/

class MaximumContinuousOnesWithFlippingMZeros {
   public:
    static void test() {
        vector<int> arr = {1, 1, 0, 1, 1, 0, 0, 1, 1, 1};
        int m = 2;

        auto size = maxWindow(arr, m);
        cout << format("Maximum window size:{} in arr:{} with m={}", size, arr, m) << endl;
    }

    static int maxWindow(vector<int>& arr, int m) {
        int mxLength = 0;
        int l = 0, r = 0;
        int zeros = 0;
        pair<int, int> window = {-1, -1};

        while (r < arr.size()) {
            if (zeros <= m) {
                if (arr[r] == 0) zeros++;
                r++;
            } else {
                if (arr[l] == 0) zeros--;
                l++;
            }

            if (r - l + 1 >= mxLength) {
                mxLength = r - l + 1;
                window = {l, r};
            }
        }

        return mxLength;
    }
};