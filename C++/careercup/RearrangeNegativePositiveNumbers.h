#pragma once
#include "../Header.h"

/*
Give you an array which has n integers,it has both positive and negative integers.Now you need sort this array in a special way.
After that,the negative integers should in the front,and the positive integers should in the back.Also the relative position should not be changed.
eg. -1 1 3 -2 2 ans: -1 -2 1 3 2.
o(n)time complexity and o(1) space complexity is perfect.
*/

/*
This can be done in O(nlogn) using divide and conquer scheme. Before starting the algorithm, please see the following observation:

Observation: given an array A, say [1, -2, ..., 4], with n elements, we can get the inverse of A, denoted as A’ (4, …, -2, 1), in \theta(n) time with O(1) space complexity.

The basic idea of the algorithm is as follows:
1. We recursively ‘sort’ two smaller arrays of size n/2 (here ‘sort’ is defined in the question)
2. Then we spend \theta(n) time merging the two sorted smaller arrays with O(1) space complexity.
How to merge?
Suppose the two sorted smaller array is A and B. A1 denotes the negative part of A, and A2 denotes positive part of A. Similarly, B1 denotes the negative part of B, and B2 denotes positive part of B.
2.1. Compute the inverse of A2 (i.e., A2’) in \theta(|A2|) time; compute the inverse of B1 (i.e., B1’) in \theta(|B1|) time. [See observation; the total time is \theta(n) and space is O(1)]
Thus the array AB (i.e., A1A2B1B2) becomes A1A2’B1’B2.
2.2. Compute the inverse of A2’B1’ (i.e., B1A2) in \theta(|A2|) time. [See observation; the total time is \theta(n) and space is O(1)]
Thus the array A1A2’B1’B2 becomes A1B1A2B2. We are done.

Time complexity analysis:
T(n) = 2T(n/2) + \theta(n) = O(nlogn)
*/
class RearrangeNegativePositiveNumbers {
public:
	static void test() {
		RearrangeNegativePositiveNumbers obj;

		{
			vector<int> input = { -1, 1, 3, -2, 2 };
			vector<int> output = input;
			obj.arrangeUsingOptimizedMergeSort(output);
			cout << format("Original array:{}, array after rearranging numbers={}", to_string(input), to_string(output)) << endl;
		}

		{
			vector<int> input = { -12, 11, -13, -5, 6, -7, 5, -3, -6 };
			vector<int> output = input;
			obj.arrangeUsingOptimizedMergeSort(output);
			cout << format("Original array:{}, array after rearranging numbers={}", to_string(input), to_string(output)) << endl;
		}
	}

	void arrangeUsingExtraSpace(vector<int>& arr) {
		vector<int> tmp;
		tmp.resize(arr.size());
		int  k = 0;
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i] < 0) tmp[k++] = arr[i];
		}
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i] > 0) tmp[k++] = arr[i];
		}
		arr = tmp;
	}

	void arrangeUsingInsSort(vector<int>& arr) {
		for (int i = 1; i < arr.size(); i++) {
			int key = arr[i];
			if (key > 0) continue;
			int j = i - 1;
			while (j >= 0 && arr[j] > 0) {
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = key;
		}
	}

	void arrangeUsingMergeSort(vector<int>& arr) {
		mergeSort(arr, 0, arr.size() - 1);
	}

	void mergeSort(vector<int>& arr, int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			mergeSort(arr, l, m);
			mergeSort(arr, m + 1, r);
			merge(arr, l, m, r);
		}
	}

	void merge(vector<int>& v, int l, int m, int r) {
		vector<int> tmp;
		tmp.resize(v.size());
		
		int i = l, j = m + 1, k = l;
		for (; i <= m && v[i] < 0; i++) tmp[k++] = v[i];
		for (; j <= r && v[j] < 0; j++) tmp[k++] = v[j];
		for (; i <= m; i++) tmp[k++] = v[i];
		for (; j <= r; j++) tmp[k++] = v[j];

		for (i = l; i <= r; i++) v[i] = tmp[i];
	}

	void arrangeUsingOptimizedMergeSort(vector<int>& arr) {
		optimizedMergeSort(arr, 0, arr.size() - 1);
	}

	void optimizedMergeSort(vector<int>& arr, int l, int r) {
		if (l < r) {
			int m = (l + r) / 2;
			optimizedMergeSort(arr, l, m);
			optimizedMergeSort(arr, m + 1, r);
			optimizedMerge(arr, l, m, r);
		}
	}

	void optimizedMerge(vector<int>& v, int l, int m, int r) {
		int i = l, j = m + 1;
		while (i <= m && v[i] < 0) i++;
		while (j <= r && v[j] < 0) j++;

		reverse(v, i, m);
		reverse(v, j, r);
		reverse(v, i, j - 1);
	}

	void reverse(vector<int>& v, int l, int r) {
		while (l < r) {
			swap(v[l++], v[r--]);
		}
	}
};