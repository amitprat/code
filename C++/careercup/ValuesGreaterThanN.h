#pragma once
#include "../Header.h"

/*
https://careercup.com/question?id=5094709806497792

Given an unsorted array of integers, you need to return maximum possible n such that the array consists at least n
values greater than or equals to n. Array can contain duplicate values.
Sample input : [1, 2, 3, 4] -- output : 2
Sample input : [900, 2, 901, 3, 1000] -- output: 3
*/

/*
Lets say the array has M numbers.For the purpose of this problem, negative values and 0s are irrelevant.Also,
numbers larger than M can be treated as M because the answer is never larger than M.

So, we can count the number of existing values between 1 and M.Then, process the values backwards(M to 1) to find
the answer, adding the counts of the values processed so far.

This yields an O(M) algorithm with extra O(M) memory.
*/
class ValuesGreaterThanN {
   public:
    static void test() {
        vector<int> input1 = {1, 2, 3, 4};
        auto res1 = valueGreaterThanN1(input1);
        cout << format("Input={}, Output={}", to_string(input1), res1) << endl;

        vector<int> input2 = {900, 2, 901, 3, 1000};
        auto res2 = valueGreaterThanN1(input2);
        cout << format("Input={}, Output={}", to_string(input2), res2) << endl;
    }

    static int valuesGreaterThanN(const vector<int>& values) {
        int n = values.size();
        vector<int> count(n + 1, 0);
        for (auto val : values)
            if (val >= n)
                count[n]++;
            else if (val > 0)  // ignore negative values
                count[val]++;
        int am = 0;
        for (int i = n; i > 0; i--) {
            am += count[i];  // amount of numbers >= i
            if (am >= i)
                return i;
        }
        return 0;
    }

    static int valueGreaterThanN1(vector<int>& arr) {
        int n = arr.size();
        vector<int> count(n + 1, 0);

        for (auto val : arr) {
            if (val >= n)
                count[n]++;
            else if (val > 0)
                count[val]++;
        }

        int right = 0;
        for (int i = n; i >= 1; i--) {
            right += count[i];
            if (right >= i) return i;
        }

        return 0;
    }
};