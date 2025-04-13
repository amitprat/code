#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/
*/

class SearchInRowColumnSortedMatrix {
   public:
    static void test() {
        SearchInRowColumnSortedMatrix obj;

        vector<vector<int>> matrix = {
            {10, 20, 30, 40},
            {15, 25, 35, 45},
            {27, 29, 37, 48},
            {32, 33, 39, 50}};

        // Function call
        auto val = obj.search(matrix, 29);
        cout << val << endl;
    }

   public:
    Point search(vector<vector<int>>& matrix, int element) {
        int n = matrix.size();
        if (n == 0) return {-1, -1};

        int m = matrix[0].size();
        int i = 0, j = m - 1;

        while (i < n && j >= 0) {
            if (element == matrix[i][j]) {
                return {i, j};
            } else if (element < matrix[i][j]) {
                j--;
            } else {
                i++;
            }
        }

        return {-1, -1};
    }
};