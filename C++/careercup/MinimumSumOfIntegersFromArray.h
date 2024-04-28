#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5678435150069760

Given the array of digits (0 is also allowed), what is the minimal sum of two integers that are made of the digits contained in the array.
For example, array: 1 2 7 8 9. The min sum (129 + 78) should be 207

Sort the array. The largest numbers should be in the least significant positions, so build up your two integers by alternating from the two arrays.
E.g. 1 3 5 7 8 9 => 1 and 3, then 15 and 37, then 158 and 379. 0 is a special case, if not allowed to use that as a leading digit then have to use it as the second digit.
*/
class MinimumSumOfIntegersFromArray {
   public:
    static void test() {
        MinimumSumOfIntegersFromArray obj;

        vector<vector<int>> inputs = {
            {1, 3, 5, 7, 8, 9},
            {1, 0, 9, 3, 2},
            {9, 2, 0, 0, 1},
            {9, 3, 9, 0, 0, 0, 0},
            {9, 2, 0, 1, 4, 7, 2, 0, 4, 1}};

        for (auto& arr : inputs) {
            cout << "Input: " << arr << endl;
            auto sum = obj.findElements(arr);
            cout << "Sum: " << sum << endl;
        }
    }

   public:
    int findElements(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        if (n == 1) return arr[0];
        if (n == 2) return arr[0] + arr[1];

        sort(arr.begin(), arr.end());

        int i = 0;
        while (i < n && arr[i] == 0) i++;

        if (i != 0) {
            swap(arr[0], arr[i]);
            if (i + 1 < n) swap(arr[1], arr[i + 1]);
        }

        cout << "Modified array: " << arr << endl;

        int a = arr[0];
        int b = arr[1];
        for (int i = 2; i < n; i++) {
            if (i % 2 == 0)
                a = a * 10 + arr[i];
            else
                b = b * 10 + arr[i];
        }

        cout << "A = " << a << ", B=" << b << endl;

        return a + b;
    }
};