#include "../Header.h"

/*
Given an array having positive integers, find a continous subarray which adds to a given number.

It can be done O(n).
Keep adding elements to a running sum till it is either equal to given number or is greater than
the given number. As soon as we add a number and the running number is greater than the given number we subtract the elements
from the beginning of the array till it is again less than the given number. After the current sum is less than the given
number we add the next element and check and continue the same process.
*/

class SubarrayWithGivenSum {
   public:
    vector<int> subarraySum(vector<int> arr, int n, long long s) {
        vector<int> positions = {-1};

        int i = 0, j = 0;
        long long cur_sum = 0;

        while (j < arr.size()) {
            if (i < j && cur_sum > s)
                cur_sum -= arr[i++];
            else
                cur_sum += arr[j++];

            if (i < j && cur_sum == s) return {i + 1, j};
        }

        while (i < j && cur_sum > s) cur_sum -= arr[i++];
        if (i < j && cur_sum == s) return {i + 1, j};

        return positions;
    }
};