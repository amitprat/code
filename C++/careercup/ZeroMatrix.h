#pragma once
#include "../header.h"

class ZeroMatrix {
   public:
    static void test() {
        vector<vector<int>> matrix = {
            {1, 2, 0, 4},
            {5, 6, 7, 8},
            {9, 0, 11, 12},
            {0, 14, 15, 16}};

        cout << "Original Matrix:" << endl;
        cout << matrix << endl;

        ZeroMatrix obj;
        obj.setZeros(matrix);

        cout << "Zeros Matrix:" << endl;
        cout << matrix << endl;
    }

   private:
    void setZeros(vector<vector<int>>& matrix) {
        int N = matrix.size();
        bool rowHasZero = false;
        bool colHasZero = false;

        for (int j = 0; j < N; j++) {
            if (matrix[0][j] == 0) rowHasZero = true;
        }

        for (int i = 0; i < N; i++) {
            if (matrix[i][0] == 0) colHasZero = true;
        }

        for (int i = 1; i < N; i++) {
            for (int j = 1; j < N; j++) {
                if (matrix[i][j] == 0)
                    matrix[i][0] = matrix[0][j] = 0;
            }
        }

        for (int i = 1; i < N; i++) {
            for (int j = 1; j < N; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
        }

        if (rowHasZero) {
            for (int j = 0; j < N; j++)
                matrix[0][j] = 0;
        }

        if (colHasZero) {
            for (int i = 0; i < N; i++)
                matrix[i][0] = 0;
        }
    }

   private:
    void setZeros2(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return;
        int m = matrix[0].size();

        bool* rows = new bool[n];
        bool* cols = new bool[m];
        memset(rows, 0, n * sizeof(bool));
        memset(cols, 0, m * sizeof(bool));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) rows[i] = cols[j] = true;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (rows[i] || cols[j]) {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};