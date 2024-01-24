#pragma once
#include "../Header.h"

class FindKClosestPoints {
public:
    static void test() {
        FindKClosestPoints obj;

        {
            vector<int> arr = { 12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56 };

            int x = 33, k = 6;

            auto res = obj.findKClosestPoints(arr, x, k);
            cout << "Res = " << to_string(res) << endl;
        }

        {
            vector<int> arr1 = { 1, 4, 5, 7 };
            vector<int> arr2 = { 10, 20, 30, 40 };
            int x = 38;

            auto res = obj.closestPair(arr1, arr2, x);
            cout << "Res = " << to_string(res) << endl;
        }

        {
            vector<int> arr1 = { 1, 5, 10, 20, 40, 80 };
            vector<int> arr2 = { 6, 7, 20, 80, 100 };
            vector<int> arr3 = { 3, 4, 15, 20, 30, 70, 80, 120 };

            vector<int> res = obj.findCommonElements(arr1, arr2, arr3);
            cout << "Common elements = " << to_string(res) << endl;
        }

        {
            {
                vector<int> arr = { 0,0,0,0,0,1,1,1 };
                auto res = obj.countOnes(arr);
                cout << "Count of 1s = " << res << endl;
            }

            {
                vector<int> arr = { 1,1,1,1,1,1,1,1 };
                auto res = obj.countOnes(arr);
                cout << "Count of 1s = " << res << endl;
            }

            {
                vector<int> arr = { 0,0,0,0,0,0,0,0 };
                auto res = obj.countOnes(arr);
                cout << "Count of 1s = " << res << endl;
            }

            {
                vector<int> arr = { 0,1,1,1,1,1,1,1 };
                auto res = obj.countOnes(arr);
                cout << "Count of 1s = " << res << endl;
            }

            {
                vector<int> arr = { 1,0,0,0,0,0,0,0 };
                auto res = obj.countOnes(arr);
                cout << "Count of 1s = " << res << endl;
            }
        }
    }

    int countOnes(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (arr[m] == 0) l = m + 1;
            else r = m;
        }
        if (arr[l] == 0) return 0;
        return arr.size() - l;
    }

    vector<int> findCommonElements(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {
        int i = 0, j = 0, k = 0;
        int l = arr1.size(), m = arr2.size(), n = arr3.size();

        vector<int> res;
        while (i < l && j < m && k < n) {
            int mn = min(arr1[i], min(arr2[j], arr3[k]));
            if (mn == arr1[i] && mn == arr2[j] && mn == arr3[k]) {
                res.push_back(arr1[i]);
            }
            if (mn == arr1[i]) i++;
            if (mn == arr2[j]) j++;
            if (mn == arr3[k]) k++;
        }

        return res;
    }

    pair<int, int> closestPair(vector<int>& arr1, vector<int>& arr2, int x) {
        int l = 0, r = arr2.size() - 1;
        int diff = INT_MAX;
        pair<int, int> res;
        while (l < arr1.size() && r >= 0) {
            if (abs(arr1[l] + arr2[r] - x) < diff) {
                diff = abs(arr1[l] + arr2[r] - x);
                res = { arr1[l],arr2[r] };
            }

            if (arr1[l] + arr2[r] < x) l++;
            else if (arr1[l] + arr2[r] > x) r--;
            else break;
        }

        return res;
    }

    vector<int> findKClosestPoints(vector<int>& arr, int x, int k) {
        int mid = findMid(arr, x, 0, arr.size() - 1);
        cout << "Mid = " << arr[mid] << endl;

        int l = mid, r = mid;
        if (mid < arr.size() - 1) r = mid + 1;

        vector<int> res;
        while (l >= 0 && r < arr.size() && k) {
            if (abs(x - arr[l]) < abs(arr[r] - x)) {
                res.push_back(arr[l--]);
            }
            else {
                res.push_back(arr[r++]);
            }

            k--;
        }

        return res;
    }

    int findMid(vector<int>& arr, int x, int l, int r) {
        if (l > r) return -1;
        if (arr[l] > x) return l;
        if (arr[r] < x) return r;

        int m = (l + r) / 2;
        if (arr[m] <= x && arr[m + 1] > x) return m;

        if (arr[m] < x) return findMid(arr, x, m + 1, r);
        return findMid(arr, x, l, m - 1);
    }
};