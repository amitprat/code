#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=6282862240202752

Given an integer array. Perform circular right shift by n.
*/

class CircularShift {
   public:
    static void test() {
        CircularShift obj;

        vector<int> arr = {1, 2, 3, 4, 5};
        obj.shiftArray(arr, arr.size(), 3);

        println("Rotated array ={0}", arr);
    }

    // shift A[0…sz-1] by n (n>0)
    void shiftArray(vector<int>& arr, int sz, int n) {
        n = n % sz;

        reverse(arr, 0, sz - 1);
        reverse(arr, 0, n - 1);
        reverse(arr, n, sz - 1);

        return;
    }

    void reverse(vector<int>& arr, int start, int end) {
        while (start < end)
            swap(arr[start++], arr[end--]);
    }
};