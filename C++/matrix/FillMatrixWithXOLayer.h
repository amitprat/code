#pragma once
#include "../header.h"

class FillMatrixWithXOLayer {
   public:
    using Point = pair<int, int>;
    static void test() {
        FillMatrixWithXOLayer obj;
        int n = 6, m = 7;

        // allocate memory
        char** matrix = new char*[n];
        for (int i = 0; i < n; i++) matrix[i] = new char[m];

        obj.fillMatrixByLayer(matrix, n, m);  // fill matrix with X and 0 layer by layer

        // print result
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cout << matrix[i][j] << " ";

            cout << endl;
        }
    }

   private:
    void fillMatrixByLayer(char** mat, int n, int m) {
        int k = (n - 1) / 2;
        char ch = 'X';

        for (int layer = 0; layer <= k; layer++) {
            // first row (except last element)
            for (int j = layer; j < m - layer - 1; j++) {
                mat[layer][j] = ch;
            }

            // last column
            for (int i = layer; i < n - layer - 1; i++) {
                mat[i][m - layer - 1] = ch;
            }

            // last row
            for (int j = m - layer - 1; j > 0; j--) {
                mat[n - layer - 1][j] = ch;
            }

            // first column
            for (int i = n - layer - 1; i > layer; i--) {
                mat[i][layer] = ch;
            }

            // swap X and O
            ch = (ch == 'X' ? 'O' : 'X');
        }
    }
};