#pragma once
#include "../Header.h"
using namespace std;

class KClosestElementToGivenValueInArray {
public:
    static void test() {
        KClosestElementToGivenValueInArray obj;
        int arr[] = { 1, 2, 4, 6, 9, 14 };
        int n = sizeof(arr) / sizeof(arr[0]);

        {
            int x = 0, k = 2;
            auto result = obj.printKclosest(arr, x, k, n);

            vector<int> input;
            for (int i = 0; i < n; i++) input.push_back(arr[i]);
            auto result1 = obj.kClosest(input, k, x);

            sort(result.begin(), result.end());
            sort(result1.begin(), result1.end());
            assert(isEqual(result, result1));

            cout << "K closest: " << to_string(result) << endl;
        }

        {
            int x = 10, k = 3;
            auto result = obj.printKclosest(arr, x, k, n);

            vector<int> input;
            for (int i = 0; i < n; i++) input.push_back(arr[i]);
            auto result1 = obj.kClosest(input, k, x);

            sort(result.begin(), result.end());
            sort(result1.begin(), result1.end());

            assert(isEqual(result, result1));

            cout << "K closest: " << to_string(result) << endl;
        }

        {
            int x = 6, k = 4;
            auto result = obj.printKclosest(arr, x, k, n);

            vector<int> input;
            for (int i = 0; i < n; i++) input.push_back(arr[i]);
            auto result1 = obj.kClosest(input, k, x);

            sort(result.begin(), result.end());
            sort(result1.begin(), result1.end());
            assert(isEqual(result, result1));

            cout << "K closest: " << to_string(result) << endl;
        }
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

    int findCrossOver(int arr[], int l, int r, int x) {
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (arr[m] > x) r = m - 1;
            else l = m;
        }

        return l;
    }

    // Another approach
    vector<int> kClosest(vector<int>& v, int k, int x)
    {
        auto res = crossoverPoint(v, 0, v.size() - 1, x);
        int l = res.first;
        int r = res.second;
        vector<int> output;
        if (l == -1 || r == -1) return output;

        while (l >= 0 && r < v.size() && output.size() < k) {
            if (abs(v[l] - x) < abs(v[r] - x))output.push_back(v[l--]);
            else output.push_back(v[r++]);
        }

        while (l >= 0 && output.size() < k) {
            output.push_back(v[l--]);
        }

        while (r < v.size() && output.size() < k) {
            output.push_back(v[r++]);
        }

        return output;
    }

    pair<int, int> crossoverPoint(vector<int> v, int l, int r, int x)
    {
        if (v[l] >= x) return { l, l + 1 };
        if (v[r] <= x) return { r - 1, r };

        if (l <= r)
        {
            int m = (l + r) / 2;
            if (v[m] >= x && v[m - 1] < x) return { m - 1, m };
            if (v[m] < x) return crossoverPoint(v, m + 1, r, x);
            return crossoverPoint(v, l, m - 1, x);
        }

        return { -1, -1 };
    }
};