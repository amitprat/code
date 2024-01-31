#pragma once
#include "../Header.h"

class KClosestElementsToGivenValueInSortedArray {
   public:
    static void test() {
        KClosestElementsToGivenValueInSortedArray obj;
        vector<int> arr = {1, 2, 4, 6, 9, 14};
        int n = sizeof(arr) / sizeof(arr[0]);
        vector<pair<int, int>> inputs = {
            {0, 2},
            {10, 3},
            {6, 4}};
        for (auto& input : inputs) {
            int x = input.first, k = input.second;
            auto result1 = obj.getKClosestElementToGivenValue1(arr, x, k);
            auto result2 = obj.getKClosestElementToGivenValue2(arr, x, k);

            sort(result1.begin(), result1.end());
            sort(result2.begin(), result2.end());
            assert(areEqual(result1, result2));

            cout << format("{0} kclosest elements to {1} are {2}", k, x, to_string(result1)) << endl;
        }
    }

   private:
    vector<int> getKClosestElementToGivenValue1(const vector<int>& arr, int x, int k) {
        int n = arr.size();

        vector<int> result;
        int l = findCrossOver(arr, 0, n - 1, x);
        int r = l + 1;
        int count = 0;

        while (l >= 0 && r < n && count++ < k) {
            if (x - arr[l] < arr[r] - x) {
                result.push_back(arr[l--]);
            } else {
                result.push_back(arr[r++]);
            }
        }

        while (l >= 0 && count++ < k) result.push_back(arr[l--]);
        while (r < n && count++ < k) result.push_back(arr[r++]);

        return result;
    }

    int findCrossOver(const vector<int>& arr, int l, int r, int x) {
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (arr[m] > x)
                r = m - 1;
            else
                l = m;
        }

        return l;
    }

   private:
    // Another approach
    vector<int> getKClosestElementToGivenValue2(const vector<int>& v, int x, int k) {
        int n = v.size();
        auto res = crossoverPoint(v, 0, n - 1, x);
        int l = res.first;
        int r = res.second;

        vector<int> output;
        if (l == -1 || r == -1) return output;

        while (l >= 0 && r < n && output.size() < k) {
            if (abs(v[l] - x) < abs(v[r] - x))
                output.push_back(v[l--]);
            else
                output.push_back(v[r++]);
        }

        while (l >= 0 && output.size() < k) {
            output.push_back(v[l--]);
        }

        while (r < n && output.size() < k) {
            output.push_back(v[r++]);
        }

        return output;
    }

    pair<int, int> crossoverPoint(vector<int> v, int l, int r, int x) {
        if (v[l] >= x) return {l, l + 1};
        if (v[r] <= x) return {r - 1, r};

        if (l <= r) {
            int m = (l + r) / 2;
            if (v[m] >= x && v[m - 1] < x) return {m - 1, m};

            if (v[m] < x) return crossoverPoint(v, m + 1, r, x);
            return crossoverPoint(v, l, m - 1, x);
        }

        return {-1, -1};
    }

   private:
    static bool areEqual(const vector<int>& first, const vector<int>& second) {
        if (first.size() != second.size()) return false;

        for (int i = 0; i < first.size(); i++) {
            if (first[i] != second[i]) return false;
        }

        return true;
    }
};