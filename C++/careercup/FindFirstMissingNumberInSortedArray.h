#pragma once
#include "../header.h"

class FindFirstMissingNumberInSortedArray {
    public:
    static void test() {
        FindFirstMissingNumberInSortedArray obj;
        vector<vector<int>> arrs = {
            {0, 1, 2, 6, 9},
            {4, 5, 10, 11},
            {0, 1, 2, 3},
            {0, 1, 2, 3, 4, 5, 6, 7, 10}
        };

        for(auto& arr : arrs) {
            auto missing = obj.findMissingNumber(arr, 0, arr.size()-1);
            cout<<"Missing number: "<<missing<<endl;
        }
    }

    public:
    int findMissingNumber(vector<int>& arr, int l, int r) {
        if(l < r) {
            int m = (l+r+1)/2;
            if(arr[l] + m -l == arr[m]) return findMissingNumber(arr, m, r);
            else return findMissingNumber(arr, l, m-1);
        }

        return l + 1 + arr[0];
    }
};