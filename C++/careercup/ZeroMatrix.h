#pragma once
#include "../header.h"

/**
 * Problem: Zero Matrix
 *
 * Given an MxN matrix, if an element is 0, set its entire row and column to 0.
 *
 * Example:
 * Input:
 *   1  2  0  4
 *   5  6  7  8
 *   9  0 11 12
 *   0 14 15 16
 *
 * Output:
 *   0  0  0  0
 *   5  0  0  8
 *   0  0  0  0
 *   0  0  0  0
 */

class ZeroMatrix {
   public:
    static void test() {
        vector<vector<int>> matrix = {
            {1, 2, 0, 4},
            {5, 6, 7, 8},
            {9, 0, 11, 12},
            {0, 14, 15, 16}};

        cout << "Original Matrix:\n";
        cout << matrix << endl;

        ZeroMatrix obj;
        obj.setZeros(matrix);

        cout << "\nZeroed Matrix:\n";
        cout << matrix << endl;
    }

   public:
    void setZeros(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        bool firstRowZero = false, firstColZero = false;

        // Check if first row has any zero
        for (int j = 0; j < cols; ++j)
            if (matrix[0][j] == 0) firstRowZero = true;

        // Check if first column has any zero
        for (int i = 0; i < rows; ++i)
            if (matrix[i][0] == 0) firstColZero = true;

        // Use first row and column as markers
        for (int i = 1; i < rows; ++i)
            for (int j = 1; j < cols; ++j)
                if (matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;

        // Apply zeroes based on markers
        for (int i = 1; i < rows; ++i)
            for (int j = 1; j < cols; ++j)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;

        // Zero out first row
        if (firstRowZero)
            for (int j = 0; j < cols; ++j)
                matrix[0][j] = 0;

        // Zero out first column
        if (firstColZero)
            for (int i = 0; i < rows; ++i)
                matrix[i][0] = 0;
    }

   public:
    // Less optimal version using O(m+n) space
    void setZeros2(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        if (rows == 0) return;
        int cols = matrix[0].size();

        vector<bool> rowZero(rows, false);
        vector<bool> colZero(cols, false);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (matrix[i][j] == 0)
                    rowZero[i] = colZero[j] = true;

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (rowZero[i] || colZero[j])
                    matrix[i][j] = 0;
    }
};
