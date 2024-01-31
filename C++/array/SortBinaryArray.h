#pragma once
#include "../header.h"

/*
https://careercup.com/question?id=5668212962230272

Given an array of integers. Move all non-zero elements to the left of all zero elements.
0 1 0 => 0 0 1
1 0 0 1 1 1 1 1 0 0 => 0 0 0 0 1 1 1 1 1 1
*/

class SortBinaryArray {
   public:
    static void test() {
        SortBinaryArray obj;
        vector<vector<int>> arrs = {
            {},
            {0},
            {1},
            {0, 0},
            {1, 1},
            {0, 1},
            {0, 1, 0},
            {1, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {1, 0, 0, 1, 1, 1, 1, 1, 0, 0}};

        for (auto arr : arrs) {
            cout << "Input: " << arr << endl;

            vector<int> arr1 = arr, arr2 = arr, arr3 = arr, arr4 = arr;
            obj.sort1(arr1);
            obj.sort2(arr2);
            obj.sort3(arr3);
            obj.sort3(arr4);

            assert(arr1 == arr2);
            assert(arr1 == arr3);
            assert(arr1 == arr4);

            cout << "Output: " << arr1 << endl;
        }
    }

   private:
    void sort1(vector<int>& arr) {
        int s = 0, e = arr.size() - 1;
        while (s < e) {
            if (arr[s] == 0)
                s++;
            else {
                if (arr[e] == 0)
                    swap(arr[s++], arr[e]);
                else
                    e--;
            }
        }
    }

   private:
    void sort2(vector<int>& arr) {
        for (int i = 0, j = 0; j < arr.size(); j++) {
            if (arr[j] == 0) swap(arr[i++], arr[j]);
        }
    }

   private:
    void sort3(vector<int>& arr) {
        int i = 0, j = arr.size() - 1;
        while (i < j) {
            if (arr[i] == 0)
                i++;
            else
                swap(arr[i], arr[j--]);
        }
    }

   private:
    void sort4(vector<int>& arr) {
        int i = 0;
        for (int j = 0; j < arr.size(); i++) {
            if (arr[j] == 0) arr[i++] = arr[j];
        }
        for (; i < arr.size(); i++) arr[i] = 1;
    }
};