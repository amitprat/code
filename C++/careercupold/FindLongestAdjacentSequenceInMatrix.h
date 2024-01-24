#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5147801809846272

Given a NxN matrix which contains all distinct 1 to n^2 numbers, write code to print sequence of increasing adjacent sequential numbers.
ex:
1 5 9
2 3 8
4 6 7

should print
6 7 8 9

Here's a very simple way to do it. Make an array of booleans (or bits) of size N^2, where arr[i-1] indicates whether i+1 is adjacent to i. Then, iterate over the matrix, checking for each cell the four neighbors and populating the relevant entry in the boolean array. Then just look for the longest run of "true" values in the boolean array, which can be done with one pass.

This approach is linear in time and space with the size of the input. The space needed is only 1 bit per element, so the constant factor is really low for space. The constant factor for time should be reasonably good as well because we only do a few array accesses and comparisons for each element in the input.

*/
class FindLongestAdjacentSequenceInMatrix
{
public:
	static void test() {
		{
			vector<vector<int>> matrix = {
				{1,5,9},
				{2,3,8},
				{4,6,7}
			};

			auto res = findLongestSeq(matrix);
			cout << to_string(res) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,4,9},
				{2,3,5},
				{8,6,7}
			};

			auto res = findLongestSeq(matrix);
			cout << to_string(res) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,4,9},
				{3,2,5},
				{8,6,7}
			};

			auto res = findLongestSeq(matrix);
			cout << to_string(res) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{5,4,9},
				{3,2,1},
				{8,6,7}
			};

			auto res = findLongestSeq(matrix);
			cout << to_string(res) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{3,4,5},
				{2,1,6},
				{9,8,7}
			};

			auto res = findLongestSeq(matrix);
			cout << to_string(res) << endl;
		}
	}

	static vector<int> findLongestSeq(vector<vector<int>> matrix)
	{
		int n = matrix.size();
		vector<bool> bits(n * n, false);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				if ((i > 0 && matrix[i][j] + 1 == matrix[i - 1][j]) ||
					(j > 0 && matrix[i][j] + 1 == matrix[i][j - 1]) ||
					(i < n - 1 && matrix[i][j] + 1 == matrix[i + 1][j]) ||
					(j < n - 1 && matrix[i][j] + 1 == matrix[i][j + 1]))
				{
					bits[matrix[i][j] - 1] = true;
				}
			}
		}

		int mxLen = 0;
		int mxStart = -1;
		int curLen = 0;
		for (int i = 0; i <= n * n; i++) {
			if (i < n * n && bits[i]) curLen++;
			else {
				if (curLen > mxLen) {
					mxLen = curLen;
					mxStart = i - curLen;
				}
				curLen = 0;
			}
		}

		vector<int> res;
		for (int i = mxStart + 1; i <= mxStart + mxLen + 1; i++) res.push_back(i);

		return res;
	}
};