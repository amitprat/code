#pragma once
#include "../header.h"

class RotateMatrixBy90DegreeLeft {
   public:
    static void test() {
        RotateMatrixBy90DegreeLeft obj;

        {
            vector<vector<int>> matrix = {
                {1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};

            cout << format("Original Matrix={}", to_string(matrix)) << endl;

            auto leftRotated = matrix;
            obj.leftRotateNByMMatrix(leftRotated);
            cout << format("Left Rotated={}", to_string(leftRotated)) << endl;

            auto rightRotated = matrix;
            obj.rightRotateNByNMatrixCyclicRoll(rightRotated);
            cout << format("Right Rotated={}", to_string(rightRotated)) << endl;
        }

        {
            vector<vector<int>> matrix = {
                {1, 2, 3, 4, 5},
                {4, 5, 6, 7, 8},
                {7, 8, 9, 0, 1},
                {2, 3, 4, 5, 6},
                {5, 6, 7, 8, 9}};

            cout << format("Original Matrix={}", to_string(matrix)) << endl;

            auto leftRotated = matrix;
            obj.leftRotateNByMMatrix(leftRotated);
            cout << format("Left Rotated={}", to_string(leftRotated)) << endl;

            auto rightRotated = matrix;
            obj.rightRotateNByNMatrixCyclicRoll(rightRotated);
            cout << format("Right Rotated={}", to_string(rightRotated)) << endl;
        }

        {
            vector<vector<int>> matrix = {{1, 2, 3}};

            cout << format("Original Matrix={}", to_string(matrix)) << endl;

            auto leftRotated = matrix;
            obj.leftRotateNByNMatrix(leftRotated);
            cout << format("Left Rotated={}", to_string(leftRotated)) << endl;
        }

        {
            vector<vector<int>> matrix = {{1}, {2}, {3}};

            cout << format("Original Matrix={}", to_string(matrix)) << endl;

            auto leftRotated = matrix;
            obj.leftRotateNByNMatrix(leftRotated);
            cout << format("Left Rotated={}", to_string(leftRotated)) << endl;
        }

        {
            vector<vector<int>> matrix = {
                {1, 2, 3, 4, 5},
                {6, 7, 8, 9, 0}};

            cout << format("Original Matrix={}", to_string(matrix)) << endl;

            auto leftRotated = matrix;
            obj.leftRotateNByNMatrix(leftRotated);
            cout << format("Left Rotated={}", to_string(leftRotated)) << endl;
        }
    }

   public:
    // Rotate square matrix 90 degrees left (counter-clockwise) in-place
    // Original:       After Left Rotation:
    // 1 2 3           3 6 9
    // 4 5 6     →     2 5 8
    // 7 8 9           1 4 7
    void leftRotateNByNMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;

        int n = matrix.size();

        // Process each concentric layer
        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;

            // Rotate elements in the current layer
            for (int i = first; i < last; i++) {
                int offset = i - first;

                // Save top element
                int top = matrix[first][i];

                // Right -> Top
                matrix[first][i] = matrix[i][last];

                // Bottom -> Right
                matrix[i][last] = matrix[last][last - offset];

                // Left -> Bottom
                matrix[last][last - offset] = matrix[last - offset][first];

                // Top -> Left
                matrix[last - offset][first] = top;
            }
        }
    }

   public:
    // Rotate any N x M matrix 90 degrees left (returns new matrix)
    vector<vector<int>> leftRotateNByMMatrix(const vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};

        int n = matrix.size();
        int m = matrix[0].size();

        // Result will be M x N (dimensions swapped)
        vector<vector<int>> result(m, vector<int>(n));

        // Map (r, c) -> (m - 1 - c, r)
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                result[m - c - 1][r] = matrix[r][c];
            }
        }

        return result;
    }

   public:
    // Rotate square matrix 90 degrees right (clockwise) using cyclic roll
    // This elegant approach handles odd-sized matrices correctly with (n+1)/2
    //  for(int i=0; i<n/2; i++)
    //    for(int j=0; j<(n+1)/2; j++)
    //        cyclic_roll(m[i][j], m[n-1-j][i], m[n-1-i][n-1-j], m[j][n-1-i]);
    // void cyclic_roll(int &a, int &b, int &c, int &d)
    // {
    //    int temp = a;
    //    a = b;
    //    b = c;
    //    c = d;
    //    d = temp;
    // }
    void rightRotateNByNMatrixCyclicRoll(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;

        int n = matrix.size();

        // For n x n matrix, iterate over the upper-left quadrant
        // n/2 rows and (n+1)/2 columns handles both even and odd dimensions
        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < (n + 1) / 2; j++) {
                // Rotate 4 elements clockwise in a cycle:
                // Top-left -> Top-right -> Bottom-right -> Bottom-left -> Top-left
                cyclicRoll(
                    matrix[i][j],                  // Top-left
                    matrix[n - 1 - j][i],          // Bottom-left (becomes top-left)
                    matrix[n - 1 - i][n - 1 - j],  // Bottom-right
                    matrix[j][n - 1 - i]           // Top-right
                );
            }
        }
    }

    // Helper: Cyclic rotation of 4 elements (a <- b <- c <- d <- a)
    void cyclicRoll(int& a, int& b, int& c, int& d) {
        int temp = a;
        a = b;
        b = c;
        c = d;
        d = temp;
    }

   public:
    // Alternative: Rotate square matrix 90 degrees right (clockwise)
    // Original:       After Right Rotation:
    // 1 2 3           7 4 1
    // 4 5 6     →     8 5 2
    // 7 8 9           9 6 3
    /*
        https://careercup.com/question?id=83756
        Write a progam to rotate a matrix by 90 degrees.
    */
    void rightRotateNByNMatrixRight(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;

        int n = matrix.size();

        for (int layer = 0; layer < n / 2; layer++) {
            int first = layer;
            int last = n - 1 - layer;

            for (int i = first; i < last; i++) {
                int offset = i - first;
                int top = matrix[first][i];

                // Left -> Top
                matrix[first][i] = matrix[last - offset][first];

                // Bottom -> Left
                matrix[last - offset][first] = matrix[last][last - offset];

                // Right -> Bottom
                matrix[last][last - offset] = matrix[i][last];

                // Top -> Right
                matrix[i][last] = top;
            }
        }
    }
};