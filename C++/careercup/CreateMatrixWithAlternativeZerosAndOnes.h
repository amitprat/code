#pragma once
#include "../header.h"

class CreateMatrixWithAlternativeZerosAndOnes {
   public:
    static void test() {
        CreateMatrixWithAlternativeZerosAndOnes obj;
        obj.createMatrixWithZerosAndOnes(4, 10);
    }

   public:
    void createMatrixWithZerosAndOnes(int n, int m) {
        vector<vector<char>> matrix(n, vector<char>(m));

        char ch = 'X';
        for (int layer = 0; layer < min(n, m) / 2; layer++) {
            for (int j = layer; j < m - layer - 1; j++) matrix[layer][j] = ch;
            for (int i = layer; i < n - layer - 1; i++) matrix[i][m - layer - 1] = ch;
            for (int j = m - layer - 1; j > layer; j--) matrix[n - layer - 1][j] = ch;
            for (int i = n - layer - 1; i > 0; i--) matrix[i][layer] = ch;

            ch = (ch == 'X') ? 'O' : 'X';
        }

        cout << matrix << endl;
    }
};