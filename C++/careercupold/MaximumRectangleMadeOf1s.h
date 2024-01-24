#pragma once
#include "../Header.h"

/*
Given a 2D array of 1 and 0, Find the largest rectangle (may not be square) which is made up of all 1 or 0.
*/
class MaximumRectangleMadeOf1s
{
public:
	static void test() {
		MaximumRectangleMadeOf1s obj;

		{
			vector<vector<int>> matrix =
			{
				{ 0, 1, 1, 0 },
				{ 1, 1, 1, 1 },
				{ 1, 1, 1, 1 },
				{ 1, 1, 0, 0 }
			};

			cout << to_string(matrix) << endl;
			cout << "Area of maximum rectangle is " << obj.maxRectangle(matrix) << endl;
		}

		{
			vector<vector<int>> matrix =
			{
				{ 0, 0, 1, 0 },
				{ 0, 1, 1, 1 },
				{ 1, 1, 1, 1 },
				{ 0, 1, 0, 0 }
			};

			cout << to_string(matrix) << endl;
			cout << "Area of maximum rectangle is " << obj.maxRectangle(matrix) << endl;
		}
	}

	int maxRectangle(vector<vector<int>> matrix)
	{
		int maxSize = 0;

		for (int i = 0; i < matrix.size(); i++) {
			if (i > 0) {
				for (int j = 0; j < matrix[i].size(); j++) {
					if (matrix[i][j] == 1) matrix[i][j] += matrix[i - 1][j];
				}
			}
			int curSize = getMaxSize(matrix[i]);
			maxSize = max(maxSize, curSize);
		}

		return maxSize;
	}

	int getMaxSize(vector<int> matrix) {
		stack<int> st;
		int i = 0;
		int mxArea = 0;

		while (i < matrix.size() || !st.empty()) {
			if (i < matrix.size() && (st.empty() || matrix[i] >= matrix[st.top()])) {
				st.push(i++);
			}
			else {
				auto height = matrix[st.top()]; st.pop();
				auto width = st.empty() ? i : (i - st.top() - 1);
				mxArea = max(mxArea, height * width);
			}
		}

		return mxArea;
	}
};