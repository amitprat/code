#pragma once
#include "../header.h"

/*
Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
*/

class Solution {
   public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> table(n, vector<int>(m, -1));
        int overallMax = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                table[i][j] = longestIncreasingPath(matrix, i, j, n, m, table);
                overallMax = max(overallMax, table[i][j]);
            }
        }

        return overallMax;
    }

    int longestIncreasingPath(vector<vector<int>>& matrix, int r, int c, int n, int m, vector<vector<int>>& table) {
        if (r < 0 || c < 0 || r >= n || c >= m) return 0;

        if (table[r][c] != -1) return table[r][c];

        int curLen = 1;
        if (r + 1 < n && matrix[r + 1][c] > matrix[r][c]) curLen = max(curLen, 1 + longestIncreasingPath(matrix, r + 1, c, n, m, table));
        if (r - 1 >= 0 && matrix[r - 1][c] > matrix[r][c]) curLen = max(curLen, 1 + longestIncreasingPath(matrix, r - 1, c, n, m, table));
        if (c + 1 < m && matrix[r][c + 1] > matrix[r][c]) curLen = max(curLen, 1 + longestIncreasingPath(matrix, r, c + 1, n, m, table));
        if (c - 1 >= 0 && matrix[r][c - 1] > matrix[r][c]) curLen = max(curLen, 1 + longestIncreasingPath(matrix, r, c - 1, n, m, table));

        table[r][c] = curLen;

        return curLen;
    }
};