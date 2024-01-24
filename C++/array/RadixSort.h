#pragma once
#include "../header.h"

class RadixSort {
public:
    static void test() {
        RadixSort obj;
        int arr[] = { 170, 45, 75, 90, 802, 24, 2, 66 };
        int n = sizeof(arr) / sizeof(int);

        cout << "Unordered arr: ";
        print(arr, n);

        obj.sort(arr, n);

        cout << "Ordered arr: ";
        print(arr, n);
    }

    bool countSort(int a[], int n, int r, int exp) {
        int* output = new int[n];
        int* count = new int[r];
        memset(count, 0, sizeof(int) * r);

        bool res = false;
        for (int i = 0; i < n; i++) {
            int v = a[i] / exp;
            count[v % 10]++;
            if (v != 0) {
                res = true;
            }
        }
        if (!res) return res;

        for (int i = 1; i < r; i++) count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            int idx = (a[i] / exp) % 10;
            output[count[idx] - 1] = a[i];
            count[idx]--;
        }

        for (int i = 0; i < n; i++) {
            a[i] = output[i];
        }
        return true;
    }

    void sort(int a[], int n) {
        for (int exp = 1;; exp *= 10) {
            bool res = countSort(a, n, 10, exp);
            if (!res) break;
        }
    }
};