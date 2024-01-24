#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5716707660267520

The "surpasser" of an element in an array is defined as the number of elements that are to the "right" and bigger than itself.

Example:
Array:
[2, 7, 5, 5, 2, 7, 0, 8, 1]
The "surpassers" are
[5, 1, 2, 2, 2, 1, 2, 0, 0]

Question: Find the maximum surpasser of the array.

In this example, maximum surpasser = 5

Merge Sort modification which sorts initial array "a" in decreasing order, but in spite of modifying given array it modifies an array of indexes "b", which allows to track surpassers in the third array "c". Array "t" is a temp buffer used for merging purposes as required by Merge Sort algorithm.
Time: O(n log n).
Space: O(n).
*/
class SurpassersOfArray
{
public:
	static void test() {
		{
			vector<int> arr = { 1,2,3,45 };

			int mxSurpasser = printSurpassersBruteForce(arr);
			cout << "mxSurpasser = " << mxSurpasser << endl;
			cout << endl;

			mxSurpasser = printSurpassersMergeSort(arr);
			cout << "mxSurpasser = " << mxSurpasser << endl;
		}

		{
			vector<int> arr = { 2, 7, 5, 5, 2, 7, 0, 8, 1 };

			int mxSurpasser = printSurpassersBruteForce(arr);
			cout << "mxSurpasser = " << mxSurpasser << endl;
			cout << endl;

			mxSurpasser = printSurpassersMergeSort(arr);
			cout << "mxSurpasser = " << mxSurpasser << endl;
		}
	}

	static int  printSurpassersBruteForce(vector<int>& arr)
	{
		int mxSurpasser = 0;
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << " : ";
			int cnt = 0;
			for (int j = i + 1; j < arr.size(); j++) {
				if (arr[j] > arr[i]) cnt++;
			}
			cout << cnt << endl;
			mxSurpasser = max(mxSurpasser, cnt);
		}

		return mxSurpasser;
	}

	static int printSurpassersMergeSort(vector<int>& arr)
	{
		vector<int> arrIndex(arr.size());
		vector<int> surpassers(arr.size(), 0);
		vector<int> tmp(arr.size());
		for (int i = 0; i < arr.size(); i++) arrIndex[i] = i;

		mergeSort(arr, 0, arr.size() - 1, tmp, arrIndex, surpassers);
		cout << "Sorted arr: " << to_string(tmp) << endl;

		int mxElem = 0;
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i] << " : " << surpassers[i] << endl;
			mxElem = max(mxElem, surpassers[i]);
		}

		return mxElem;
	}

	static void mergeSort(vector<int>& arr, int l, int r, vector<int>& tmp, vector<int>& arrIndex, vector<int>& surpassers)
	{
		if (l < r) {
			int m = (l + r) / 2;
			mergeSort(arr, l, m, tmp, arrIndex, surpassers);
			mergeSort(arr, m + 1, r, tmp, arrIndex, surpassers);
			merge(arr, l, m, r, tmp, arrIndex, surpassers);
		}
	}

	static void merge(vector<int>& arr, int l, int m, int r, vector<int>& tmp, vector<int>& arrIndex, vector<int>& surpassers)
	{
		int i = l, j = m + 1, k = l, acc = 0;
		while (i <= m || j <= r) {
			if (j > r || (i <= m && arr[arrIndex[i]] >= arr[arrIndex[j]])) {
				tmp[k++] = arrIndex[i];
				surpassers[arrIndex[i]] += acc;
				i++;
			}
			else {
				tmp[k++] = arrIndex[j];
				acc++;
				j++;
			}
		}
		for (int x = l; x <= r; x++) arrIndex[x] = tmp[x];
	}
};