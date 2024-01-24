#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=19016700

Given 2 arrays.Imagine you are making bst from each array.u need to tell whether 2 bsts will be identical or not without actually constructing the tree.
Ex:
2 3 1
2 1 3
will construct the same tree
A1[]={2,1,3}
2
1 3

A2[]={2,3,1}
2
1 3
*/
class CompareTwoBsts {
public:
    static void test() {
        vector<int> arr1 = { 2,3,1 };
        vector<int> arr2 = { 2,1,3 };

        auto res = isSame(arr1, arr2, 0, arr1.size() - 1, 0, arr2.size() - 1);
        cout << res << endl;
    }

    static bool isSame(vector<int>& arr1, vector<int>& arr2, int l1, int r1, int l2, int r2) {
        if (l1 == r1 && l2 == r2) return true;
        if (l1 >= r1 || l2 >= r2) return false;
        if (arr1[l1] != arr2[l2]) return false;

        int firstArrL1 = l1, firstArrR1 = r1, secondArrL1 = l2, secondArrR2 = r2;
        bool leftSmall1 = true, leftSmall2 = true;
        //while (firstArrL1 <= r1 && arr1[firstArrL1] != arr1[l1]) {
        //    if()
        //    firstArrL1++;
        //}
        //while (j1 <= r2 && arr2[j1] != arr2[l2]) j1++;
    }
};