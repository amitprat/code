#pragma once
#include "../header.h"
/*
Given an array of integers (positive or negative) find the lowest positive integer NOT present in that array.
Step 1: Disregard all negatives (put all the positives in the front of the array)
Step 2: Say the number of positive numbers is: N.
        we can divide the array into two parts: <=N and >N (the part <=N is first, the >N is second)
Step 3: For every number x in the array <=N, swap it with the number at index x. Do not swap repeats.
Step 4: Scan through the numbers and find the first number that does not match its index.
*/
class FindFirstMissingPositive {
   public:
    static void test() {
        vector<vector<int>> inputs = {
            {2, 3, -7, 6, 8, 1, -10, 15},
            {1, 5, 3, 0},
            {10, 50, 30, 0},
            {1, 4, 3, 2}};

        for (auto& input : inputs) {
            cout << to_string(input) << ", ";
            int res = firstMissingPositive(input);
            cout << "First missing positive: " << res << endl;
        }
    }

    static int firstMissingPositive(vector<int>& arr) {
        for (int i = 0; i < arr.size();) {
            if (i + 1 == arr[i])  // if the element and index matching (index=elem-1)
                i++;
            else if (arr[i] <= 0 || arr[i] >= arr.size())  // ignore numbers out of range
                i++;
            else {
                int pos = arr[i] - 1;  // get element index position
                if (pos + 1 == arr[pos])
                    i++;  // if the element is already in correct position, then continue (duplicates)
                else
                    swap(arr[i], arr[pos]);  // else move the element to correct position without moving
            }
        }

        for (int i = 0; i < arr.size(); i++) {
            if (i + 1 != arr[i]) return i + 1;
        }

        return arr.size() + 1;
    }
};