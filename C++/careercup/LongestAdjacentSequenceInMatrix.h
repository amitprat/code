#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5147801809846272

Given a NxN matrix which contains all distinct 1 to n^2 numbers, write code to print sequence of increasing adjacent sequential numbers.
ex:
1 5 9
2 3 8
4 6 7

should print
6 7 8 9

Here's a very simple way to do it. Make an array of booleans (or bits) of size N^2, where arr[i-1] indicates whether i+1 is adjacent to i.
Then, iterate over the matrix, checking for each cell the four neighbors and populating the relevant entry in the boolean array.
Then just look for the longest run of "true" values in the boolean array, which can be done with one pass.

This approach is linear in time and space with the size of the input. The space needed is only 1 bit per element,
so the constant factor is really low for space. The constant factor for time should be reasonably good as well
because we only do a few array accesses and comparisons for each element in the input.
*/

class LongestAdjacentSequenceInMatrix {
   public:
    static void test() {
        using Matrix = vector<vector<int>>;
        vector<Matrix> matrices = {
            // matrix 1
            {{1, 5, 9},
             {2, 3, 8},
             {4, 6, 7}},

            // matrix 2
            {{1, 4, 9},
             {2, 3, 5},
             {8, 6, 7}},

            // matrix 3
            {{1, 4, 9},
             {3, 2, 5},
             {8, 6, 7}},

            // matrix 4
            {{5, 4, 9},
             {3, 2, 1},
             {8, 6, 7}},

            // matrix 5
            {{3, 4, 5},
             {2, 1, 6},
             {9, 8, 7}}};

        for (auto& matrix : matrices) {
            auto res = longestSequence(matrix);
            cout << to_string(res) << endl;
        }
    }

   private:
    static pair<int, int> longestSequence(vector<vector<int>> mat) {
        auto l1 = longestSequenceRec(mat);
        auto l2 = longestSequenceDP(mat);
        auto l3 = longestSeqUsingBitset(mat);

        assert(l1.first == l2.first);
        assert(l1.second == l2.second);
        assert(l1.first == l3.first);
        assert(l1.second == l3.second);

        return l1;
    }

   private:
    static pair<int, int> longestSequenceRec(vector<vector<int>> mat) {
        int start = 0, longest = 0;
        int n = mat.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int curLongest = longestSequenceRec(mat, i, j, n);
                if (curLongest > longest) {
                    start = mat[i][j];
                    longest = curLongest;
                }
            }
        }

        return {start, longest};
    }

    static int longestSequenceRec(vector<vector<int>> mat, int r, int c, int n) {
        int longest = 1;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) != abs(j)) {
                    int nr = r + i;
                    int nc = c + j;

                    if (!isValid(nr, nc, n) || mat[r][c] + 1 != mat[nr][nc]) continue;

                    int curLongest = 1 + longestSequenceRec(mat, nr, nc, n);
                    longest = max(longest, curLongest);
                }
            }
        }

        return longest;
    }

    static bool isValid(int r, int c, int n) {
        return !(r < 0 || c < 0 || r >= n || c >= n);
    }

   private:
    static pair<int, int> longestSequenceDP(vector<vector<int>> mat) {
        int n = mat.size();
        vector<vector<int>> memo(n, vector<int>(n, -1));

        int start = 0, longest = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (memo[i][j] == -1) {
                    int curLongest = longestSequenceDP(mat, i, j, n, memo);
                    if (curLongest > longest) {
                        start = mat[i][j];
                        longest = curLongest;
                    }
                }
            }
        }

        return {start, longest};
    }

    static int longestSequenceDP(vector<vector<int>> mat, int r, int c, int n, vector<vector<int>>& memo) {
        if (memo[r][c] != -1) return memo[r][c];

        int longest = 1;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) == abs(j)) continue;
                int nr = r + i;
                int nc = c + j;

                if (!isValid(nr, nc, n) || mat[r][c] + 1 != mat[nr][nc]) continue;

                int curLongest = 1 + longestSequenceDP(mat, nr, nc, n, memo);
                longest = max(longest, curLongest);
            }
        }

        memo[r][c] = longest;

        return memo[r][c];
    }

   private:
    static pair<int, int> longestSeqUsingBitset(vector<vector<int>> matrix) {
        int n = matrix.size();
        vector<bool> bits(n * n, false);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if ((i > 0 && matrix[i][j] + 1 == matrix[i - 1][j]) ||
                    (j > 0 && matrix[i][j] + 1 == matrix[i][j - 1]) ||
                    (i < n - 1 && matrix[i][j] + 1 == matrix[i + 1][j]) ||
                    (j < n - 1 && matrix[i][j] + 1 == matrix[i][j + 1])) {
                    bits[matrix[i][j] - 1] = true;
                }
            }
        }

        int mxLen = 0;
        int mxStart = -1;
        int curLen = 0;
        for (int i = 0; i <= n * n; i++) {
            if (i < n * n && bits[i]) {
                curLen++;
            } else {
                if (curLen > mxLen) {
                    mxLen = curLen;
                    mxStart = i - curLen;
                }
                curLen = 0;
            }
        }

        for (int i = mxStart + 1; i <= mxStart + mxLen + 1; i++) {
            cout << i << " ";
        }
        cout << endl;

        return {mxStart + 1, mxLen + 1};
    }
};