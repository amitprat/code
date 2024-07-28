#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5631660689195008

Given an array of elements, return an array of values pertaining to how many elements are greater than that element remaining in the array.
Brute force is obvious, but must be done faster than O(n^2)

Ex. [3,4,5,9,2,1, 3]
Return [3, 2, 1, 0, 1, 1, 0]
First element is 3 because 3<4,5,9. Second element is 2 because 4< 5,9 etc
*/
class NumberOfElementsGreaterOnRight {
   public:
    static void test() {
        NumberOfElementsGreaterOnRight obj;
        vector<int> arr = {3, 4, 5, 9, 2, 1, 3};
        auto res = obj.numElementsOnRight(arr);
        cout << "Result: " << res << endl;
    }

   public:
    vector<int> numElementsOnRight(vector<int>& arr) {
        vector<int> tmp(arr.size());
        vector<int> cnt(arr.size(), 0);

        mergeSort(arr, 0, arr.size() - 1, tmp, cnt);

        return cnt;
    }

    void mergeSort(vector<int>& arr, int l, int r, vector<int>& tmp, vector<int>& cnt) {
        if (l >= r) return;

        int m = (l + r) / 2;

        mergeSort(arr, l, m, tmp, cnt);
        mergeSort(arr, m + 1, r, tmp, cnt);
        merge(arr, l, m, r, tmp, cnt);
    }

    void merge(vector<int>& arr, int l, int m, int r, vector<int>& tmp, vector<int>& cnt) {
        int i = l, j = m + 1;
        int k = l;

        while (i <= m && j <= r) {
            if (arr[i] < arr[j]) {
                cnt[i] += (r - j);
                tmp[k++] = arr[i++];
            } else {
                tmp[k++] = arr[j++];
            }
        }

        for (i = l; i <= r; i++) arr[i] = tmp[i];
    }
};