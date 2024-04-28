#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/
*/

class MatrixSizeSquareSubMatrixWithAllOnes {
   public:
    static void test() {
        MatrixSizeSquareSubMatrixWithAllOnes obj;
        vector<vector<int>> matrices = {
            {0, 1, 1, 0, 1},
            {1, 1, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1},
            {0, 0, 0, 0, 0}};

        auto res1 = obj.maximumSizeMatrix1(matrices);
        cout << "Max size = " << res1 << endl;

        auto res2 = obj.maximumSizeMatrix2(matrices);
        cout << "Max size = " << res2 << endl;
    }

   public:
    int maximumSizeMatrix1(vector<vector<int>> matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        int m = matrix[0].size();

        int maxSize = 1;
        Point start = {-1, -1};
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] = 1 + min(matrix[i - 1][j - 1], min(matrix[i - 1][j], matrix[i][j - 1]));
                } else {
                    matrix[i][j] = 0;
                }
                if (matrix[i][j] > maxSize) {
                    maxSize = matrix[i][j];
                    start = {i - maxSize + 1, j - maxSize + 1};
                }
            }
        }

        print(matrix, start, maxSize);

        return maxSize;
    }

   public:
    int maximumSizeMatrix2(vector<vector<int>> matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        int m = matrix[0].size();

        int maxSize = 0;

        vector<vector<int>> dp(n, vector<int>(m));
        for (int j = 0; j < m; j++) {
            dp[0][j] = matrix[0][j];
            if (dp[0][j] == 1) maxSize = 1;
        }
        for (int i = 0; i < n; i++) {
            dp[i][0] = matrix[i][0];
            if (dp[i][0] == 1) maxSize = 1;
        }

        Point start = {-1, -1};
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = 1 + min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]));
                } else {
                    dp[i][j] = 0;
                }

                if (dp[i][j] > maxSize) {
                    maxSize = dp[i][j];
                    start = {i - maxSize + 1, j - maxSize + 1};
                }
            }
        }

        print(matrix, start, maxSize);

        return maxSize;
    }

   private:
    void print(vector<vector<int>>& matrix, Point start, int n) {
        for (int i = start.x; i < start.x + n; i++) {
            for (int j = start.y; j < start.y + n; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};