#pragma once
#include "../Header.h"

class InversionCount {
public:
    static void test() {
        vector<int> arr = { 1, 20, 6, 4, 5 };
        InversionCount obj;
        cout << "Inversions = " << obj.count(arr) << endl;

        return;
    }

    int count(vector<int>& arr) {
        vector<int> tmp(arr.size());
        return mergeSort(arr, tmp, 0, arr.size() - 1);
    }

    int mergeSort(vector<int>& arr, vector<int>& tmp, int l, int r) {
        int invCount = 0;
        if (l < r) {
            int m = (l + r) / 2;
            invCount += mergeSort(arr, tmp, l, m);
            invCount += mergeSort(arr, tmp, m + 1, r);

            invCount += merge(arr, tmp, l, m + 1, r);
        }
        return invCount;
    }

    int merge(vector<int>& arr, vector<int>& tmp, int l, int m, int r) {
        int count = 0;
        int i = l, j = m, k = l;
        while (i < m || j <= r) {
            if (i < m && j <= r) {
                if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
                else {
                    count += m - i;
                    tmp[k++] = arr[j++];
                }
            }
            else if (i < m) tmp[k++] = arr[i++];
            else if (j <= r) tmp[k++] = arr[j++];
        }
        k = l;
        while (k <= r) {
            arr[k] = tmp[k]; k++;
        }
        return count;
    }
};