#pragma once
#include "../header.h"

/*
 * A 2-D array of 1's and 0's is given. Find the row with max 1's.
 * The array is sorted row wise (all 0's in a row are followed by all 1's).
 */

class FindRowWithMaxOnes {
   public:
    static void test() {
        vector<vector<int>> arr = {
            {0, 1, 1, 1},
            {0, 0, 1, 1},
            {1, 1, 1, 1},
            {0, 0, 0, 0}};

        FindRowWithMaxOnes obj;
        int res1 = obj.findRowWithMaxOnes1(arr);
        int res2 = obj.findRowWithMaxOnes1(arr);
        assert(res1 == res2);

        cout << "Max row: " << res1 << endl;
    }

   private:
    int findRowWithMaxOnes1(vector<vector<int>>& arr) {
        if (arr.size() == 0) return -1;

        int i = 0;
        int j = arr[0].size() - 1;

        int row = -1;
        while (i < arr.size() && j >= 0) {
            if (arr[i][j]) {
                j--;
                row = i;
            } else {
                i++;
            }
        }

        return row;
    }

   private:
    int findRowWithMaxOnes2(vector<vector<int>>& arrs) {
        int total_max = 0;
        int cur_max = 0;

        for (auto& arr : arrs) {
            int start = binary_search(arr, 0, arr.size() - 1);
            cur_max = arr.size() - start;
            total_max = max(total_max, cur_max);
        }

        return total_max;
    }

    int binary_search(vector<int>& arr, int s, int e) {
        if (s > e) return -1;
        int m = (s + e + 1) / 2;
        cout << m << endl;

        if (arr[m] == 1)
            return binary_search(arr, s, m - 1);
        else
            return binary_search(arr, m, e);
    }
};