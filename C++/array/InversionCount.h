#pragma once
#include "../header.h"

/*
Input: arr[] = {8, 4, 2, 1}
Output: 6
Explanation: Given array has six inversions: (8, 4), (4, 2), (8, 2), (8, 1), (4, 1), (2, 1).

Input: arr[] = {1, 20, 6, 4, 5}
Output: 5
Explanation: Given array has five inversions: (20, 6), (20, 4), (20, 5), (6, 4), (6, 5).
*/

class InversionCount {
   public:
    static void test() {
        InversionCount obj;

        vector<vector<int>> arrs = {
            {1, 20, 6, 4, 5},
            {8, 4, 2, 1},
            {1, 2, 3, 4, 5},
            {5, 4, 3, 2, 1}};

        for (const auto& arr : arrs) {
            int ans1 = obj.countInversions(arr);
            int ans2 = obj.getInvCountNaive(arr);

            assert(ans1 == ans2);

            cout << "Number of inversions are " << ans1;
        }
    }

   private:
    int countInversions(vector<int> arr) {
        vector<int> tmp(arr.size());
        return mergeSort(arr, 0, arr.size() - 1, tmp);
    }

    int mergeSort(vector<int>& arr, int l, int r, vector<int>& tmp) {
        if (l < r) {
            int m = (l + r) / 2;
            int inv = mergeSort(arr, l, m, tmp);
            inv += mergeSort(arr, m + 1, r, tmp);
            inv += merge(arr, l, m, r, tmp);
            return inv;
        }

        return 0;
    }

    int merge(vector<int>& arr, int l, int m, int r, vector<int>& tmp) {
        int inv = 0;
        int i = l, j = m + 1, k = l;

        for (; i <= m && j <= r; k++) {
            if (arr[i] <= arr[j]) {
                tmp[k] = arr[i++];
            } else {
                tmp[k] = arr[j++];
                inv += m - i + 1;
            }
        }

        while (i <= m) {
            tmp[k++] = arr[i++];
        }

        while (j <= r) {
            tmp[k++] = arr[j++];
        }

        for (i = l; i <= r; i++) arr[i] = tmp[i];

        // cout << "Inv = " << inv << endl;

        return inv;
    }

   private:
    int getInvCountNaive(const vector<int>& arr) {
        int n = arr.size();

        int inv_count = 0;
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (arr[i] > arr[j])
                    inv_count++;

        return inv_count;
    }
};