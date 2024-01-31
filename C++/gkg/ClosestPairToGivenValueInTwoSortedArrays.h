#pragma once
#include "../header.h"

class ClosestPairToGivenValueInTwoSortedArrays {
   public:
    static void test() {
        ClosestPairToGivenValueInTwoSortedArrays obj;

        vector<int> arr1 = {1, 4, 5, 7};
        vector<int> arr2 = {10, 20, 30, 40};

        for (int x = 1; x <= 50; x++) {
            auto res = obj.closestPair(arr1, arr2, x);
            cout << std::format("Pair closest to {} is :[{},{}]", x, res.first, res.second) << endl;
        }
    }

    pair<int, int> closestPair(vector<int>& arr1, vector<int>& arr2, int x) {
        int l = 0, r = arr2.size() - 1;
        int diff = INT_MAX;
        pair<int, int> res;

        while (l < arr1.size() && r >= 0) {
            if (abs(arr1[l] + arr2[r] - x) < diff) {
                diff = abs(arr1[l] + arr2[r] - x);
                res = {arr1[l], arr2[r]};
            }

            if (arr1[l] + arr2[r] < x)
                l++;
            else if (arr1[l] + arr2[r] > x)
                r--;
            else
                break;
        }

        return res;
    }
};