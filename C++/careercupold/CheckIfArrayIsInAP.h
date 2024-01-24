#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5724684365594624

Check if an integer array is arithmetic sequence.

Example: 1, 2, 3, 4, 5, 6, 7, 8 => true
1, 3, 5, 7, 9 => true

Array may not be sorted.
*/
class CheckIfArrayIsInAP {
public:
    static void test() {

    }

    /*
    First iteration:
        find min and max of array
        calculate xor of all values of array elements

    calcultate d = (mx - mn)/(n-1);

    Second iteration:
        for all element from mn to mx with d as increment:
            xor ^= element

    if xor == 0 then AP otherwise not.

    Why xor is required: because array is unsorted. If array was sorted, we could have compare adjacent array values to validate but if array is unsorted, then we have 2 options:
            1) sort the array and then perform adjacency check
            2) use xor method to check if all predicted element in mn to mx range with 'd' as diff are present in array if any of them isn't present, then the final xor won't be zero.
    */
    bool isAP(vector<int>& arr) {
        int mn = INT_MAX, mx = INT_MIN;
        int xorVal = 0;
        int n = arr.size();
        for (auto e : arr) {
            mn = min(mn, e);
            mx = max(mx, e);

            xorVal ^= e;
        }
        int d = (mx - mn) / (n - 1);

        for (int s = mn; s <= mx; s += d) {
            xorVal ^= s;
        }

        return xorVal == 0;
    }
};