#pragma once
#include "../Header.h"

class CountInSortedArray {
public:
    static void test() {
        CountInSortedArray obj;
        vector<int> arr = { 8, 8, 8, 9, 9, 11, 15, 16, 16, 16 };
        for (int i = 0; i < 20; i++) {
            cout << i << " = " << obj.count(arr, i) << ", " << obj.countUsingIndex(arr, i) << endl;
        }
    }

    int count(vector<int> arr, int x) {
        return count(arr, 0, arr.size() - 1, x);
    }

    int count(vector<int> arr, int l, int r, int x) {
        if (l > r) return 0;
        int m = (l + r) / 2;
        if (arr[m] > x) return count(arr, l, m - 1, x);
        else if (arr[m] < x) return count(arr, m + 1, r, x);
        else {
            int left = 0, right = 0;
            if (arr[r] > x) right = count(arr, m + 1, r - 1, x);
            else right = r - m;
            if (arr[l] < x) left = count(arr, l + 1, m - 1, x);
            else left = m - l;
            return left + right + 1;
        }
    }

    int countUsingIndex(vector<int> arr, int x) {
        int right = rightIndex(arr, 0, arr.size() - 1, x);
        int left = leftIndex(arr, 0, arr.size() - 1, x);
        if (left == -1 || right == -1) return 0;
        return right - left + 1;
    }

    int leftIndex(vector<int> arr, int l, int r, int x) {
        if (l > r) return 0;
        if (l == r) return arr[l] == x ? l : -1;
        int m = (l + r) / 2;
        if (arr[m] >= x) return leftIndex(arr, l, m, x);
        return leftIndex(arr, m + 1, r, x);
    }

    int rightIndex(vector<int> arr, int l, int r, int x) {
        if (l > r) return 0;
        if (l == r) return arr[l] == x ? l : -1;
        int m = (l + r + 1) / 2;
        if (arr[m] <= x) return rightIndex(arr, m, r, x);
        return rightIndex(arr, l, m - 1, x);
    }
};