#pragma once
#include "../header.h"

class SortedRotatedArraySearchAndPivot {
public:
    static void test() {
        SortedRotatedArraySearchAndPivot obj;
        vector<vector<int>> tests{
            {},
            {0},
            {0,1},
            {10,1},
            {0,10,100},
            {100,0,10},
            {10,100,0},
            {0,2,3,4,5,6,7,8},
            {3,4,5,6,7,8,0,2},
            {6,7,8,0,2,3,4,5},
            {4,5,6,7,8,0,2,3},
            {3,4,5,6,7,8,0,2},
            {2,3,4,5,6,7,8,0},
        };

        srand(time(nullptr));
        for (auto& test : tests) {
            auto pivot = obj.findPivot(test);

            int randIndex = rand() % (test.size() + 1);
            int x = randIndex < test.size() ? test[randIndex] : rand() % 1000;
            auto searchRes = obj.search(test, x);

            cout << format("Pivot in array={} is found at index={},value={}", to_string(test), pivot, (pivot != -1 ? test[pivot] : INT_MIN)) << endl;
            cout << format("Search X={} in array={} is found at index={},value={}", x, to_string(test), searchRes, (searchRes != -1 ? test[searchRes] : INT_MIN)) << endl;
            cout << endl;
        }
    }

    // minimum element
    int findPivot(vector<int>& v) {
        if (v.empty()) return -1;
        int l = 0, r = v.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (v[m] > v[r]) l = m + 1;
            else r = m;
        }
        return l;
    }

    // search element in array
    int search(vector<int>& arr, int x) {
        return search(arr, 0, arr.size() - 1, x);
    }

    int search(vector<int>& arr, int l, int r, int x) {
        if (l > r) return -1;

        int m = (l + r) / 2;
        if (arr[m] == x) return m;

        if (arr[m] <= arr[r]) {
            // second half is sorted
            if (x > arr[m] && x <= arr[r]) return search(arr, m + 1, r, x);
            return search(arr, l, m - 1, x);
        }
        else {
            // first half is sorted
            if (x >= arr[l] && x < arr[m]) return search(arr, l, m - 1, x);
            return search(arr, m + 1, r, x);
        }
    }

    // search element in array second method (using offset)
    int searchElementInArrayUsingOffset(vector<int>& nums, int target) {
        if (nums.empty()) return -1;

        // find pivot
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] > nums[hi]) lo = mid + 1;
            else hi = mid;
        }

        // now bsearch with rotation as offset
        int rot = lo;
        lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int realmid = (mid + rot) % nums.size();
            if (nums[realmid] == target) return realmid;
            if (target < nums[realmid]) hi = mid - 1;
            else lo = mid + 1;
        }

        return -1;
    }
};