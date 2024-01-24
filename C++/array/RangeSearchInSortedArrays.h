#pragma once
#include "../header.h"
using namespace std;

class RangeSearchInSortedArrays {
public:
    static void test() {
        RangeSearchInSortedArrays obj;
        vector<int> arr = { 1,1,1,1,2,2,2,3,3,4,4,4,5,6,6,6,6 };

        for (int i = 0; i < 10; i++) {
            auto res = obj.searchRange(arr, i);
            cout << format("Search for element={} in array={}, found between={}", i, to_string(arr), to_string(res)) << endl;
            if (res[0] != -1) {
                cout << "Output array: " << to_string(arr, res[0], res[1]) << endl;
            }
            cout << endl;
        }
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result = { -1,-1 };
        if (nums.empty()) return result;

        // search for left
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (target > nums[m]) l = m + 1;
            else r = m;
        }
        if (nums[l] != target) return result;
        else result[0] = l;

        // search for right
        l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (target < nums[m]) r = m - 1;
            else l = m;
        }
        if (nums[r] == target) result[1] = r;

        return result;
    }
};