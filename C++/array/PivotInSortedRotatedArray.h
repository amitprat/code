#include "../header.h"

/*
https://careercup.com/question?id=4872867141386240

Write a program for finding a minimum element in rotated sorted array(either ascending or descending ) and array contains duplicates.
*/
class PrivotInSortedRotatedArray {
   public:
    static void test() {
        PrivotInSortedRotatedArray obj;
        vector<vector<int>> tests{
            {},
            {0},
            {0, 1},
            {10, 1},
            {0, 10, 100},
            {100, 0, 10},
            {10, 100, 0},
            {0, 2, 3, 4, 5, 6, 7, 8},
            {3, 4, 5, 6, 7, 8, 0, 2},
            {6, 7, 8, 0, 2, 3, 4, 5},
            {4, 5, 6, 7, 8, 0, 2, 3},
            {3, 4, 5, 6, 7, 8, 0, 2},
            {2, 3, 4, 5, 6, 7, 8, 0},
        };

        for (auto& test : tests) {
            cout << "Pivot = " << obj.pivot(test) << endl;
        }
    }

    int pivot(vector<int>& v) {
        if (v.empty()) return -1;
        int l = 0, r = v.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (v[m] > v[r])
                l = m + 1;
            else
                r = m;
        }
        return v[l];
    }
};