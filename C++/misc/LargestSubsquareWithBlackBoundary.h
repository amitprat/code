/* Cracking the coding interview
20.11 Imagine you have a square matrix, where each cell is filled with either black or white. Design an algorithm to find the maximum subsquare such that all four borders are filled with black pixels.
Assumption: Square is of size NxN.
This algorithm does the following:
1. Iterate through every (full) column from left to right.
2. At each (full) column (call this currentColumn), look at the subcolumns (from biggest to smallest).
3. At each subcolumn, see if you can form a square with the subcolumn as the left side. If so, update currentMaxSize and go to the next (full) column.
4. If N - currentColumn <= currentMaxSize, then break completely. We’ve found the largest square possible. Why? At each column, we’re trying to create a square with that column as the left side. The largest such square we could possibly create is N - currentColumn. Thus, if N-currentColumn <= currentMaxSize, then we have no need to proceed.
Time complexity: O(N^2).
*/

#include "../header.h"

class LargestSubsquareWithBlackBoundary {
   public:
    static void test() {
        vector<vector<int>> matrix = {
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {0, 1, 1, 1},
            {1, 0, 1, 1}};
        LargestSubsquareWithBlackBoundary obj;
        auto result = obj.findLargestSubsqaure(matrix);
        cout << format("Largest subsquare is of size={}, starting at row={}, col={}", get<2>(result), get<0>(result), get<1>(result)) << endl;
    }

   private:
    tuple<int, int, int> findLargestSubsqaure(vector<vector<int>>& matrix) {
        int maxSz = 0;
        int col = 0;
        int N = matrix.size();
        tuple<int, int, int> result;

        while (N - col > maxSz) {
            for (int row = 0; row < N; row++) {
                int size = N - max(row, col);
                while (size > maxSz) {
                    if (isSquareWithBlackBoundary(matrix, row, col, size)) {
                        maxSz = size;
                        result = {row, col, size};
                        break;
                    }
                    size--;
                }
            }
            col++;
        }
        return result;
    }

    bool isSquareWithBlackBoundary(vector<vector<int>>& matrix, int r, int c, int sz) {
        // check first and last column for each row
        for (int i = r; i < r + sz; i++) {
            if (!matrix[i][c] || !matrix[i][c + sz - 1])
                return false;
        }

        // check first and last row for each column
        for (int i = c; i < c + sz; i++) {
            if (!matrix[r][i] || !matrix[r + sz - 1][i])
                return false;
        }
        return true;
    }
};