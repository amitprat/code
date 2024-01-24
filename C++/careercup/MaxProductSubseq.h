#pragma once
#include "../Header.h"

/*
Given a sequence of non-negative integers find a subsequence of length 3 having maximum product with the numbers of the subsequence
being in ascending order.
Example:
Input: 6 7 8 1 2 3 9 10
Ouput: 8 9 10
*/

/*
6 7 8 1 2 3 9 10
0   6   7   8   8   8   8   9
10  10  10  10  10  10  10  0
*/

class MaxProductSubseq
{
public:
	static void test() {
		vector<int> arr = { 6, 7, 8, 1, 2, 3, 9, 10 };
		auto res = findSubsequenceWithMaxProduct(arr);

		cout << format("Maximum product subsequence in arr:{} is {} with product={}", to_string(arr), to_string(res.second), res.first) << endl;
	}

	static pair<int, vector<int>> findSubsequenceWithMaxProduct(vector<int>& arr) {
		int mxProduct = 0;
		vector<int> result;

		for (int i = 1; i < arr.size() - 1; i++) {
			int leftHighestLower = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (arr[j] < arr[i] && arr[j] > leftHighestLower) {
					leftHighestLower = arr[j];
				}
			}

			int rightHighestHigher = 0;
			for (int j = i + 1; j < arr.size(); j--) {
				if (arr[j] > arr[i] && arr[j] > rightHighestHigher) {
					rightHighestHigher = arr[j];
				}
			}

			int curMax = leftHighestLower * arr[i] * rightHighestHigher;
			if (curMax > mxProduct) {
				mxProduct = curMax;
				result = { leftHighestLower , arr[i], rightHighestHigher };
			}
		}

		return { mxProduct, result };
	}
};

/*
public static int[] findSubsequenceWithMaxProduct(int[] inputArray) {
		int maxProduct = 0;
		int[] subsequenceWithLargestProduct = new int[3];
		for (int i = 1; i < inputArray.length - 1; i++) {
			int leftLowest = 0;
			int rightHighest = 0;
			// find lowest on the left.
			for (int j = 0; j < i; j++) {
				if (inputArray[j] < inputArray[i] && inputArray[j] > leftLowest) {
					leftLowest = inputArray[j];
				}
			}
			// find highest on right.
			for (int k = i + 1; k < inputArray.length; k++) {
				if (inputArray[k] > inputArray[i] && inputArray[k] > rightHighest) {
					rightHighest = inputArray[k];
				}
			}
			int currentProduct = inputArray[i] * leftLowest * rightHighest;
			if (currentProduct > maxProduct) {
				maxProduct = currentProduct;
				subsequenceWithLargestProduct = new int[]{leftLowest, inputArray[i], rightHighest};
			}
		}
		return subsequenceWithLargestProduct;
	}
*/