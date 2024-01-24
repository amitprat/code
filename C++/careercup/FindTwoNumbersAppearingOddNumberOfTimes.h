#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=16306671

You are given an integer array, where all numbers except for TWO numbers appear even number of times.

Q: Find out the two numbers which appear odd number of times.

1. XOR all the n numbers.
2. Result will be knocked out for all the even pairs as a^a=0 The result now contains only XOR of the two odd out numbers.
3. Find the first bit position in the result that is 1. Definitely this bit position both the odd numbers have different bit values. i.e. one has a 0 and another has a 1 at this position. Let this position be x
4. XOR the elements that have 1 at x bit position and XOR the elements that have 0 at x bit position. The two XOR results would give the two odd count numbers.
*/
class FindTwoNumbersAppearingOddNumberOfTimes {
   public:
    static void test() {
        vector<int> arr = {1, 2, 5, 4, 3, 1, 5, 3, 1, 3, 2, 4, 1, 7};
        auto res = findNumbers(arr);

        cout << to_string(res) << endl;
    }

    static vector<int> findNumbers(vector<int>& arr) {
        int xorVal = 0;
        for (auto num : arr) xorVal ^= num;

        int i = 0;
        for (; i < 32; i++) {
            if (xorVal & (1 << i)) break;
        }

        int num1 = 0;
        int num2 = 0;
        for (int num : arr) {
            if (num & (1 << i))
                num1 ^= num;
            else
                num2 ^= num;
        }

        return {num1, num2};
    }
};