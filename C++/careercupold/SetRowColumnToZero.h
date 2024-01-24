#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=4959773472587776

Given an n X n matrix, find all elements which are zero, when found set all the elements in that row and column to zero.
*/
class SetRowColumnToZero {
public:
	static void test() {
		{
			vector<vector<int>> arr = {
				{1, 2, 3, 4},
				{5, 6, 7, 8 },
				{9, 0, 1, 0 },
				{3, 4, 5, 6 }
			};

			setRowColumnsToZero(arr);

			cout << to_string(arr) << endl;
		}

		{
			vector<vector<int>> arr = {
				{1, 2, 3, 4},
				{5, 6, 7, 8 },
				{9, 0, 1, 0 },
				{3, 4, 5, 6 }
			};

			setRowColumnsToZero2(arr);

			cout << to_string(arr) << endl;
		}
	}

	static void setRowColumnsToZero(vector<vector<int>>& matrix) {
		bool rowHasZero = false, colHasZero = false;
		for (int i = 0; i < matrix.size(); i++) if (matrix[i][0] == 0) rowHasZero = true;
		for (int j = 0; j < matrix[0].size(); j++) if (matrix[0][j] == 0) colHasZero = true;

		for (int i = 1; i < matrix.size(); i++) {
			for (int j = 1; j < matrix[i].size(); j++) {
				if (matrix[i][j] == 0) {
					matrix[i][0] = matrix[0][j] = 0;
				}
			}
		}

		for (int i = 1; i < matrix.size(); i++) {
			for (int j = 1; j < matrix[i].size(); j++) {
				if (matrix[i][0] == 0 || matrix[0][j] == 0) {
					matrix[i][j] = 0;
				}
			}
		}

		if (rowHasZero) {
			for (int i = 0; i < matrix.size(); i++) matrix[i][0] = 0;
		}

		if (colHasZero) {
			for (int j = 0; j < matrix[0].size(); j++) matrix[0][j] = 0;
		}
	}

	static void setRowColumnsToZero2(vector<vector<int>>& matrix) {
		int n = matrix.size();
		int m = matrix[0].size();
		bool* rows = new bool[n];
		bool* cols = new bool[m];
		memset(rows, false, n * sizeof(bool));
		memset(cols, false, m * sizeof(bool));

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				if (matrix[i][j] == 0) {
					rows[i] = cols[j] = true;
				}
			}
		}

		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[i].size(); j++) {
				if (rows[i] || cols[j]) {
					matrix[i][j] = 0;
				}
			}
		}
	}
};