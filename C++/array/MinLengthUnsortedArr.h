#pragma once
#include "../header.h"
using namespace std;

class MinLengthUnsortedArr
{
public:
	static void test()
	{
		vector<vector<int>> v = {
			{},
			{1,2,3},
			{3,2,1},
			{1,3,2},
			{1,1,1},
			{10, 12, 20, 30, 25,40, 32, 31, 35, 50, 60}
		};

		for (auto arr : v) {
			auto unsortedSubArray = minLengthUnsortedSubArr(arr);
			cout << format("Input={}, Min Len unordered subarray={}", to_string(arr), to_string(unsortedSubArray)) << endl;
		}
	}

	static vector<int> minLengthUnsortedSubArr(vector<int>& v)
	{
		int s = 0, e = v.size() - 1;
		while (s < e && v[s] <= v[s + 1]) s++;
		while (e > s && v[e] >= v[e - 1]) e--;
		if (s >= e) return {};

		int minElem = v[s], maxElem = v[e];
		for (int i = s; i <= e; i++) {
			minElem = min(minElem, v[i]);
			maxElem = max(maxElem, v[i]);
		}

		while (s >= 0 && v[s] > minElem) s--;
		while (e <= v.size() - 1 && v[e] < maxElem) e++;

		vector<int> result;
		for (int i = s + 1; i < e; i++) result.push_back(v[i]);

		return result;
	}
};