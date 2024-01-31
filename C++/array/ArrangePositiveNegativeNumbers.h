#pragma once
#include "../header.h"

/*
Rearrange negative and positive numbers such that
negative numbers comes first and then positive numbers
but keeping the original order of numbers.

Input: 1 2 3 -23 -1 -1 -2 -3 -12 -24 -121 11 12 12 1212
Output: -23 -1 -1 -2 -3 -12 -24 -121 1 2 3 11 12 12 1212
*/

class ArrangePositiveNegativeNumbers {
   public:
    static void test() {
        ArrangePositiveNegativeNumbers obj;
        vector<int> test = {1, 2, 3, -23, -1, -1, -2, -3, -12, -24, -121, 11, 12, 12, 1212};
        vector<int> expected = {-23, -1, -1, -2, -3, -12, -24, -121, 1, 2, 3, 11, 12, 12, 1212};
        cout << "Input: " << test << endl;

        vector<int> testcopy = test;
        obj.arrangeNumbersNormalSort(testcopy);
        assert(expected == testcopy);

        vector<int> testcopy = test;
        obj.arrangeNumbersMergeSort(testcopy);
        assert(expected == testcopy);

        cout << "Output: " << test << endl;
    }

   private:
    // T = O(n^2)
    // As we do rightshift for every element of array
    void arrangeNumbersNormalSort(vector<int>& v) {
        normalSort(v);
    }

    void normalSort(vector<int>& v) {
        for (int cur = 0; cur < v.size(); cur++) {
            if (v[cur] >= 0) rightShift(v, cur);  // find the first positive element and see if its in correct position
        }
    }

    void rightShift(vector<int>& v, int curPositivePos) {
        if (curPositivePos == v.size()) return;  // if positive number is at end, return.

        int nextNegPos = curPositivePos + 1;                               // look negative number of right of positive number
        while (nextNegPos < v.size() && v[nextNegPos] >= 0) nextNegPos++;  // find next negative number

        // no negative number found on right.
        if (nextNegPos == v.size()) return;

        int nextNeg = v[nextNegPos];  // store the negative number

        for (int i = nextNegPos - 1; i >= curPositivePos; i--) v[i + 1] = v[i];  // right shift all the positive number and make room for negative number
        v[curPositivePos] = nextNeg;                                             // place negative number
    }

   private:
    // T = O(nlogn)
    void arrangeNumbersMergeSort(vector<int>& v) {
        mergeSort(v, 0, v.size() - 1);
    }

    void mergeSort(vector<int>& v, int l, int r) {
        if (l < r) {
            int m = (l + r) / 2;
            mergeSort(v, l, m);
            mergeSort(v, m + 1, r);
            merge(v, l, m, r);
        }
    }

    void merge(vector<int>& v, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        int* left = new int[n1];
        int* right = new int[n2];

        for (int i = l, j = 0; i <= m; i++, j++) left[j] = v[i];
        for (int i = m + 1, j = 0; i <= r; i++, j++) right[j] = v[i];

        // copy the negative numbers from start of both left and right arrays.
        int k = l;
        int i = 0, j = 0;
        for (; i < n1 && j < n2;) {
            if (left[i] < 0)
                v[k++] = left[i++];
            else if (right[j] < 0)
                v[k++] = right[j++];
            else
                break;
        }

        // copy the remaning positive numbers
        for (; i < n1; i++, k++) {
            v[k] = left[i];
        }

        for (; j < n2; j++, k++) {
            v[k] = right[j];
        }
    }
};