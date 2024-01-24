#pragma once
#include "../Header.h"

class PrimeExtensible {
public:
    static void test() {
        vector<int> arr = { 2,3,7,11 };
        int n = 100;
        print(arr, n);
    }

    static void print(vector<int>& arr, int n) {
        vector<int> result;
        vector<int> indices(arr.size(), 0);
        result.push_back(1);

        for (int i = 1; i < n; i++) {
            int mn = getMin(arr, indices, result);
            result.push_back(mn);
        }

        cout << result << endl;
    }

    static int getMin(vector<int>& arr, vector<int>& indices, vector<int>& result) {
        int mn = INT_MAX;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] * result[indices[i]] < mn) mn = arr[i] * result[indices[i]];
        }
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] * result[indices[i]] == mn) {
                indices[i]++;
            }
        }

        return mn;
    }
};