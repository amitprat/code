#pragma once
#include "../Header.h"

class SplitArrayInTwoPartsWithMinimumDiff
{
public:
	static void test() {
		SplitArrayInTwoPartsWithMinimumDiff obj;
		vector<int> arr = { 1,2,4,1,2,5,32,42,2,6,3,1,2,62,4,6 };
		vector<int> arr1, arr2;
		obj.splitArrays(arr, arr1, arr2);

		cout << to_string(arr1) << ": " << accumulate(arr1.begin(), arr1.end(), 0) << endl;
		cout << to_string(arr2) << ": " << accumulate(arr2.begin(), arr2.end(), 0) << endl;

		obj.splitArraysUsingDP(arr, arr1, arr2);

		SplitArray1 obj1;
		obj1.splitArray(arr);
	}

	bool splitArrays(vector<int>& arr, vector<int>& arr1, vector<int>& arr2)
	{
		int totalElements = arr.size();
		if (totalElements & 1) return false;

		vector<int> indices;
		int minSum = INT_MAX;
		int totalSum = accumulate(arr.begin(), arr.end(), 0);

		splitArrays(arr, 0, totalElements, totalElements / 2, 0, totalSum / 2, minSum, {}, indices);

		int j = 0;
		for (int i = 0; i < totalElements; i++) {
			if (j < indices.size() && i == indices[j]) {
				arr1.push_back(arr[i]);
				j++;
			}
			else {
				arr2.push_back(arr[i]);
			}
		}

		return true;
	}

	void splitArrays(vector<int>& arr, int index, int totalElements, int halfElements, int curSum, int halfSum, int& minSum, vector<int> curIndices, vector<int>& indices)
	{
		if (halfElements == 0)
		{
			if (abs(curSum - halfSum) < minSum) {
				indices = curIndices;
				minSum = abs(curSum - halfSum);
			}
			return;
		}
		if (halfSum < 0 || index >= totalElements) return;

		splitArrays(arr, index + 1, totalElements, halfElements, curSum, halfSum, minSum, curIndices, indices);
		curIndices.push_back(index);
		splitArrays(arr, index + 1, totalElements, halfElements - 1, curSum + arr[index], halfSum, minSum, curIndices, indices);
		curIndices.pop_back();
	}

	// https://www.careercup.com/question?id=10244832
	void splitArraysUsingDP(vector<int>& arr, vector<int>& arr1, vector<int>& arr2)
	{
		int total = accumulate(arr.begin(), arr.end(), 0) / 2;
		int sz = arr.size() / 2;

		vector<vector<bool>> memo(sz + 1, vector<bool>(total + 1, false));
		memo[0][0] = true;

		for (int i = 0; i < arr.size(); i++) //consider taking i-th item 
		{
			for (int k = sz - 1; k >= 0; k--) //each item must be taken once, hence loop backwards
			{
				for (int j = 0; j <= total - arr[i]; j++)
				{
					if (memo[k][j] && arr[i] + j <= total)
						memo[k + 1][j + arr[i]] = true;
				}
			}
		}

		for (int j = total; j >= 1; j--) {
			if (memo[sz][j]) {
				cout << "sum : " << j << endl;
				break;
			}
		}
	}

	class SplitArray1 {
	public:
		bool splitArray(vector<int>& arr) {
			int n = arr.size();
			if (n & 1) return false;

			int s = accumulate(arr.begin(), arr.end(), 0);

			int diff = INT_MAX;
			vector<int> indices;
			splitArray(arr, 0, n, s, 0, 0, {}, diff, indices);

			vector<int> arr1, arr2;
			for (int i = 0, j = 0; i < n; i++) {
				if (j < n / 2 && indices[j] == i) {
					arr1.push_back(arr[i]);
					j++;
				}
				else {
					arr2.push_back(arr[i]);
				}
			}

			cout << to_string(arr1) << " with sum = " << accumulate(arr1.begin(), arr1.end(), 0) << endl;
			cout << to_string(arr2) << " with sum = " << accumulate(arr2.begin(), arr2.end(), 0) << endl;

			return true;
		}

		void splitArray(vector<int>& arr, int idx, int n, int totalSum,
			int curSetSize, int curSum, vector<int> curSet, int& diff, vector<int>& indices)
		{
			if (curSetSize == n / 2) {
				int curDiff = abs(totalSum - 2 * curSum);
				if (curDiff < diff) {
					diff = curDiff;
					indices = curSet;
					return;
				}
			}

			if (idx >= n || curSetSize > n / 2) return;

			splitArray(arr, idx + 1, n, totalSum, curSetSize, curSum, curSet, diff, indices);

			curSet.push_back(idx);
			splitArray(arr, idx + 1, n, totalSum, curSetSize + 1, curSum + arr[idx], curSet, diff, indices);
			curSet.pop_back();
		}
	};
};