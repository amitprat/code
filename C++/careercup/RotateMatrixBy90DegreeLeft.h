#pragma once
#include "../Header.h"

class RotateMatrixBy90DegreeLeft {
public:
	static void test() {
		RotateMatrixBy90DegreeLeft obj;

		{
			vector<vector<int>> matrix = {
				{1,2,3},
				{4,5,6},
				{7,8,9}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			obj.rotateNByNMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,2,3,4,5},
				{4,5,6,7,8},
				{7,8,9,0,1},
				{2,3,4,5,6},
				{5,6,7,8,9}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			obj.rotateNByNMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,2,3}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			matrix = obj.rotateNByMMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1},
				{2},
				{3}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			matrix = obj.rotateNByMMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,2,3,4,5},
				{6,7,8,9,0}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			matrix = obj.rotateNByMMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,2,3},
				{4,5,6},
				{7,8,9}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			matrix = obj.rotateNByMMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}

		{
			vector<vector<int>> matrix = {
				{1,2,3,4,5},
				{4,5,6,7,8},
				{7,8,9,0,1},
				{2,3,4,5,6},
				{5,6,7,8,9}
			};

			cout << format("Input={}", to_string(matrix)) << endl;
			matrix = obj.rotateNByMMatrix(matrix);
			cout << format("Output={}", to_string(matrix)) << endl;
		}
	}
	void rotateNByNMatrix(vector<vector<int>>& matrix) {
		int n = matrix.size();
		for (int i = 0; i < n / 2; i++) {
			rotateNByNMatrix(matrix, i, matrix[i].size());
		}
	}

	void rotateNByNMatrix(vector<vector<int>>& matrix, int level, int m) {
		for (int j = level; j < m - level - 1; j++) {
			int tmp = matrix[level][j];
			matrix[level][j] = matrix[m - j - 1][level];
			matrix[m - j - 1][level] = matrix[m - level - 1][m - j - 1];
			matrix[m - level - 1][m - j - 1] = matrix[j][m - level - 1];
			matrix[j][m - level - 1] = tmp;
		}
	}

	vector<vector<int>> rotateNByMMatrix(vector<vector<int>>& matrix) {
		int n = matrix.size();
		vector<vector<int>> result;
		if (n == 0) return result;
		int m = matrix[0].size();

		for (int c = m - 1; c >= 0; c--) {
			vector<int> newRow;
			for (int r = 0; r < n; r++) {
				newRow.push_back(matrix[r][c]);
			}
			result.push_back(newRow);
		}

		return result;
	}
};