#pragma once
#include "../Header.h"

// https://www.geeksforgeeks.org/find-the-longest-path-in-a-matrix-with-given-constraints/
class LongestIncreasingSequenceInMatrix {
public:
	static void test() {
		{
			vector<vector<int>> mat =
			{
				{ 1, 2, 9 },
				{ 5, 3, 8 },
				{ 4, 6, 7 }
			};

			cout << to_string(mat) << endl;
			auto l1 = longestSequence(mat);
			cout << "Result = " << to_string(l1) << endl;
			cout << "Longest subsequence: ";
			for (auto i = l1.first; i < l1.first + l1.second; i++) {
				cout << i << " ";
			}
			cout << endl;
		}

		{
			vector<vector<int>> mat =
			{
				{ 1, 2, 8 },
				{ 9, 3, 7 },
				{ 4, 5, 6 }
			};

			cout << to_string(mat) << endl;
			auto l1 = longestSequence(mat);
			cout << "Result = " << to_string(l1) << endl;
			cout << "Longest subsequence: ";
			for (auto i = l1.first; i < l1.first + l1.second; i++) {
				cout << i << " ";
			}
			cout << endl;
		}
	}

	static pair<int, int> longestSequence(vector<vector<int>> mat) {
		auto l1 = longestSequenceRec(mat);
		auto l2 = longestSequenceDP(mat);

		assert(l1.first == l2.first);
		assert(l1.second == l2.second);

		return l1;
	}

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

		return { start, longest };
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

		return { start, longest };
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
};