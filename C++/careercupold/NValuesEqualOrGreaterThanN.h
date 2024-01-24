#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5094709806497792

Given an unsorted array of integers, you need to return maximum possible n such that the array consists at least n values greater
than or equals to n.
Array can contain duplicate values.
Sample input : [1, 2, 3, 4] -- output : 2
Sample input : [900, 2, 901, 3, 1000] -- output: 3
*/

class NValuesEqualOrGreaterThanN
{
public:
	static void test()
	{
		NValuesEqualOrGreaterThanN obj;
		{
			vector<int> arr = { 1, 2, 3, 4 };
			int n = obj.getN(arr);
			cout << format("Maximum possible n={} in array={}", n, to_string(arr)) << endl;
		}

		{
			vector<int> arr = { 900, 2, 901, 3, 1000 };
			int n = obj.getN(arr);
			cout << format("Maximum possible n={} in array={}", n, to_string(arr)) << endl;
		}

		{
			vector<int> arr = { 900, 950, 901, 900, 1000 };
			int n = obj.getN(arr);
			cout << format("Maximum possible n={} in array={}", n, to_string(arr)) << endl;
		}
	}

	int getN(vector<int>& arr)
	{
		int n = arr.size();
		vector<int> cnt(n + 1, 0);
		for (auto e : arr) {
			if (e < 0) continue;
			if (e >= n) cnt[n]++;
			else cnt[e]++;
		}

		int right = 0;
		for (int i = n; i >= 1; i--) {
			right += cnt[i];
			if (right >= i) return i;
		}

		return 0;
	}
};