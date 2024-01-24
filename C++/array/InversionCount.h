#pragma once
#include "../Header.h"

class InversionCount
{
public:
	static void test() {
		InversionCount obj;
		vector<int> arr = { 1, 20, 6, 4, 5 };
		int ans = obj.countInversions(arr);
		cout << " Number of inversions are " << ans;
	}

private:
	int countInversions(vector<int> arr)
	{
		vector<int> tmp(arr.size());
		return mergeSort(arr, 0, arr.size() - 1, tmp);
	}

	int merge(vector<int>& arr, int l, int m, int r, vector<int>& tmp)
	{
		int inv = 0;
		int i = l, j = m + 1, k = l;
		for (; i <= m && j <= r; k++) {
			if (arr[i] <= arr[j]) {
				tmp[k] = arr[i++];
			}
			else {
				tmp[k] = arr[j++];
				inv += m - i + 1;
			}
		}
		while (i <= m) { tmp[k++] = arr[i++]; }
		while (j <= r) { tmp[k++] = arr[j++]; }

		for (i = l; i <= r; i++) arr[i] = tmp[i];

		cout << "Inv = " << inv << endl;
		return inv;
	}

	int mergeSort(vector<int>& arr, int l, int r, vector<int>& tmp)
	{
		if (l < r) {
			int m = (l + r) / 2;
			int inv = mergeSort(arr, l, m, tmp);
			inv += mergeSort(arr, m + 1, r, tmp);
			inv += merge(arr, l, m, r, tmp);
			return inv;
		}
		return 0;
	}
};