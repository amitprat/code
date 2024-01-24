#pragma once
#include "../Header.h"

class IsSameTree {
public:
    static void test() {
        IsSameTree obj;
        vector<int> arr1 = { 2,3,1 };
        vector<int> arr2 = { 2,1,3 };

        cout << "Same " << obj.isSame(arr1, arr2) << endl;
    }

    bool isSame(vector<int> arr1, vector<int> arr2) {
        int i = 0, j = 0;
        return isSame(arr1, i, INT_MIN, INT_MAX, arr2, j, INT_MIN, INT_MAX);
    }

    bool isSame(vector<int> arr1, int& idx1, int mn1, int mx1,
        vector<int> arr2, int& idx2, int mn2, int mx2) {
        if (idx1 == arr1.size() && idx2 == arr2.size()) return true;
        if (idx1 >= arr1.size() || idx2 >= arr2.size()) return true;

        if (arr1[idx1] <= mn1 || arr1[idx1] >= mx1 || arr2[idx2] <= mn2 || arr2[idx2] >= mx2) return false;

        if (arr1[idx1++] != arr2[idx2++]) return false;

        return isSame(arr1, idx1, mn1, arr1[idx1], arr2, idx2, mn2, arr2[idx2])
            || isSame(arr1, idx1, arr1[idx1], mx1, arr2, idx2, arr2[idx2], mx2);
    }
};