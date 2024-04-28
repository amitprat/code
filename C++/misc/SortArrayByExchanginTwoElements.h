#pragma once
#include "../header.h"

/*
Given an array with elements check if just by exchanging two elements of the array we get a sorted array.
ex: {10, 50, 30, 40, 20, 60} [swapped 20 and 50]
ex: {10, 60, 30, 40, 50, 20} [swapped 20 and 60]
ex: {60, 20, 30, 40, 50, 10} [swapped 10 and 60]
ex: {20, 10, 30, 40, 50, 60} [swapped 10 and 20]

Time restriction: O(NlogN)
space restriction: 2N
*/

class SortArrayByExchanginTwoElements {
   public:
    bool correctArray(vector<int>& arr) {
        int first = -1, second = -1;
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) {
                if (second == -1) {
                    first = i - 1;
                    second = i;
                } else {
                    second = i;
                }
            }
        }
        if (first == -1 || second == -1) return false;
        swap(arr[first], arr[second]);

        for (int i = 1; i < arr.size(); i++) {
            if (arr[i - 1] > arr[i]) return false;
        }

        return true;
    }
};