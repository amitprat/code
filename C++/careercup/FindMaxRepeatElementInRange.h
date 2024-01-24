#pragma once
#include "../Header.h"

/*
Following is the O(n) time and O(1) extra space approach. Let us understand the approach with a simple example where arr[] = {2, 3, 3, 5, 3, 4, 1, 7}, k = 8, n = 8 (number of elements in arr[]).

1) Iterate though input array arr[], for every element arr[i], increment arr[arr[i]%k] by k (arr[] becomes {2, 11, 11, 29, 11, 12, 1, 15 })

2) Find the maximum value in the modified array (maximum value is 29). Index of the maximum value is the maximum repeating element (index of 29 is 3).

3) If we want to get the original array back, we can iterate through the array one more time and do arr[i] = arr[i] % k where i varies from 0 to n-1.
*/
class FindMaxRepeatElement {
public:
	int findMaxRepeatElem(vector<int> v, int k, int n) {
		for (auto e : v) {
			v[e % k] += k;
		}

		int mxIndex = -1;
		for (int i = 0; i < n; i++) {
			if (mxIndex == -1) mxIndex = i;
			else if (v[i] > v[mxIndex]) mxIndex = i;
		}

		for (int i = 0; i < n; i++) {
			v[i] = v[i] % k;
		}

		return mxIndex;
	}

	static void test() {
		FindMaxRepeatElement obj;
		vector<int> arr = { 2, 3, 3, 5, 3, 4, 1, 7 };
		int k = 8;
		int n = 8;

		cout << obj.findMaxRepeatElem(arr, k, n) << endl;
	}
};