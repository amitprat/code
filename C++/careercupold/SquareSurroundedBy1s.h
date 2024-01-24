#pragma once
#include "../Header.h"

class SquareSurroundedBy1s {
	bool debug = true;
public:
	static void test() {
		SquareSurroundedBy1s obj;

		{
			vector<vector<bool>> mat =
			{
				{0,1,0,0,1},
				{1,0,1,0,1},
				{0,1,1,1,0},
				{0,1,0,1,1},
				{1,1,1,1,0}
			};

			auto res = obj.largestArea(mat);
			cout << "The size of largest square sub-matrix is " << res << endl;
		}
		cout << endl;

		{
			vector<vector<bool>> mat =
			{
				{ 1, 1, 1, 1, 1, 1 },
				{ 1, 0, 1, 1, 0, 1 },
				{ 0, 1, 1, 0, 0, 1 },
				{ 1, 1, 1, 1, 1, 1 },
				{ 1, 0, 0, 1, 0, 1 },
				{ 1, 0, 1, 1, 0, 0 },
				{ 1, 0, 1, 0, 1, 1 },
				{ 1, 1, 1, 0, 1, 1 }
			};
			auto res = obj.largestArea(mat);
			cout << "The size of largest square sub-matrix is " << res << endl;
		}
	}

	int largestArea(vector<vector<bool>> mat) {
		vector<vector<pair<int, int>>> memo(mat.size(), vector<pair<int, int>>(mat[0].size()));
		for (int i = 0; i < mat.size(); i++) {
			for (int j = 0; j < mat[i].size(); j++) {
				if (mat[i][j]) {
					if (i == 0 && j == 0) memo[i][j] = { 1,1 };
					else if (i == 0) memo[i][j] = { 1,memo[i][j - 1].second + 1 };
					else if (j == 0) memo[i][j] = { memo[i - 1][j].first + 1,1 };
					else memo[i][j] = { memo[i - 1][j].first + 1,memo[i][j - 1].second + 1 };
				}
			}
		}

		if (debug) {
			for (int i = 0; i < memo.size(); i++) {
				for (int j = 0; j < memo[i].size(); j++) {
					cout << setw(4) << to_string(memo[i][j]) << " ";
				}
				cout << endl;
			}
		}

		int maxLen = 0;
		for (int i = memo.size() - 1; i >= 1; i--) {
			for (int j = memo[i].size() - 1; j >= 1; j--) {
				int curLen = min(memo[i][j].first, memo[i][j].second);
				while (curLen) {
					bool isSquare = (memo[i - curLen + 1][j].second >= curLen)
						&& (memo[i][j - curLen + 1].first >= curLen);
					if (isSquare && curLen > maxLen) {
						maxLen = curLen; break;
					}
					curLen--;
				}
			}
		}


		return maxLen;
	}
};