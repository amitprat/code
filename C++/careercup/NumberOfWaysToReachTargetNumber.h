#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=16230693

given an int array with no duplicate numbers, write a function to return number of ways to calculate a target number.

example: given {2,4,6,8} Target = 12
2 + 4 + 6 = 12,
4 + 8 = 12,
6 + 8 - 2 = 12,
2 - 4 + 6 + 8 = 12,

return 4
*/
class NumberOfWaysToReachTargetNumber {
   public:
    static void test() {
        vector<int> arr = {2, 4, 6, 8};
        int target = 12;

        numWays(arr, target);
    }

    int numWays(vector<int>& arr, int target) {
        unordered_set<int> s;
        int ways = 0;

        for (auto& e : arr) {
        }
    }
};