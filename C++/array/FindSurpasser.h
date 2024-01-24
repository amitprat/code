#pragma once
#include "../Header.h"

class FindSurpasser {
public:
	static void test() {
		FindSurpasser obj;
		{
			vector<int> arr = { 2, 7, 5, 3, 0, 8, 1 };
			auto res = obj.findSurpassers(arr);
			cout << to_string(res) << endl;
		}

		{
			vector<int> arr = { 1,2,3,4 };
			auto res = obj.findSurpassers(arr);
			cout << to_string(res) << endl;
		}

		{
			vector<int> arr = { 4,3,2,1 };
			auto res = obj.findSurpassers(arr);
			cout << to_string(res) << endl;
		}
	}

	vector<int> findSurpassers(vector<int>& arr) {
		vector<int> result;
		unordered_map<int, int> map;
		vector<int> dup = arr;

		int n = arr.size();
		vector<int> tmp(n);
		mergeSort(dup, 0, n - 1, tmp, map);

		for (int i = 0; i < n; i++) {
			result.push_back(n - i - 1 - map[arr[i]]);
		}

		return result;
	}

	void mergeSort(vector<int>& dup, int l, int r, vector<int>& tmp, unordered_map<int, int>& map) {
		if (l >= r) return;

		int m = (l + r) / 2;
		mergeSort(dup, l, m, tmp, map);
		mergeSort(dup, m + 1, r, tmp, map);
		merge(dup, l, m, r, tmp, map);
	}

	void merge(vector<int>& dup, int l, int m, int r, vector<int>& tmp, unordered_map<int, int>& map) {
		int i = l, j = m + 1, k = l;
		int inversions = 0;
		while (i <= m && j <= r) {
			if (dup[i] <= dup[j]) {
				map[dup[i]] += inversions;
				tmp[k++] = dup[i++];
			}
			else {
				inversions++; // count larger elements on left, (inversions)
				tmp[k++] = dup[j++];
			}
		}

		while (i <= m) {
			map[dup[i]] += inversions;
			tmp[k++] = dup[i++];
		}

		while (j <= r) tmp[k++] = dup[j++];

		for (i = l; i <= r; i++) dup[i] = tmp[i]; // copy back the tmp array
	}
};