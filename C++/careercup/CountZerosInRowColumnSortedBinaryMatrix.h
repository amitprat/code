#include "../header.h"

/*
https://careercup.com/question?id=5767203879124992

You are given a matrix with N rows and N columns. Elements in matrix can be either 1 or 0. Each row and column of matrix is sorted in ascending order.
Find number of 0-s in the given matrix.
Example:

0 0 1
0 1 1
1 1 1
Answer: 3

0 0
0 0
Answer: 4
Update: Expected complexity is O(log(N)). The best I've seen in comments is still O(N).

Update2: Alright, guys, sorry for a bit of trolling. Obviously this is not possible to do faster than O(N).
Here is why: take a diagonal (N, 1), (N-1, 2), ... (1, N). Suppose input matrix has all 0's above this diagonal and all 1's under this diagonal.
So only diagonal elements vary. Clearly, diagonal elements do not depend on each other. So we have to analyze each diagonal element which is O(N).

Here is an approach walking along the diagonal. General approach:
1. Start in the bottom left corner.
2. Subtract row index until you find a 0.
3. Add the row index + 1 to you total and move one column right.
4. Repeat from step 2 until you find the top or right edge of the matrix.

This is worst case O(N) since the length of the diagonal is proportional to N.

Code:
private int countNumZeroes(int[][] matrix) {
    int row = matrix.length - 1, col = 0, numZeroes = 0;
    while (col < matrix[0].length) {
      while (matrix[row][col] != 0) {
        if (--row < 0) {
          return numZeroes;
        }
      }
      // Add one since matrix index is 0 based
      numZeroes += row + 1;
      col++;
    }
    return numZeroes;
  }
*/
class CountZerosInRowColumnSortedBinaryMatrix {
   private:
    int count(vector<vector<int>>& mat) {
        int n = mat.size();
        int row = n - 1;
        int col = 0;
        Point lefBottom(row, col);

        int count = 0;
        while (row >= 0 && col < n) {
            while (mat[row][col]) row--;
            count += row + 1;
            col += 1;
        }

        return count;
    }
};