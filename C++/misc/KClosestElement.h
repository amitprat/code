#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

class KClosestElement {
public:
    static void test() {
        KClosestElement obj;
        int arr[] = { 1, 2, 4, 6, 9, 14 };
        int n = sizeof(arr) / sizeof(arr[0]);
        int x = 0, k = 2;
        auto result = obj.printKclosest(arr, x, k, n);

        cout << "K closest: ";
        for (auto r : result) {
            cout << r << " ";
        }
        cout << endl;
    }

    vector<int> printKclosest(int arr[], int x, int k, int n) {
        vector<int> result;
        int l = findCrossOver(arr, 0, n - 1, x);
        int r = l + 1;
        int count = 0;

        while (l >= 0 && r < n && count++ < k) {
            if (x - arr[l] < arr[r] - x) {
                result.push_back(arr[l--]);
            }
            else {
                result.push_back(arr[r++]);
            }
        }

        while (l >= 0 && count++ < k) result.push_back(arr[l--]);
        while (r < n && count++ < k) result.push_back(arr[r++]);

        return result;
    }

private:
    int findCrossOver(int arr[], int l, int r, int x) {
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] > x) r = m - 1;
            else l = m;
        }

        return l;
    }
};