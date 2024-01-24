#pragma once
#include "../header.h"
using namespace std;

class IterativeQuickSort
{
public:
	static void test()
	{
		IterativeQuickSort obj;
		vector<vector<int>> v = {
			{1,3,2,5,23,62,42,3},
			{3,6,23,6,34,24,6,6,23},
			{3,42,5,2,42,3,2,52,5,23},
			{1,1,1,1,1,1,1},
			{9,8,7,6,5,4,3,2,1},
			{1,2,3,4,5,6,6,7,8,9}
		};

		for (auto& arr : v) {
			cout << "Before: " << to_string(arr) << endl;

			obj.quickSort2(arr);
			cout << "After : " << to_string(arr) << endl;
		}
	}

	void quickSort(vector<int>& v)
	{
		stack<pair<int, int>> st;
		st.push({ 0,v.size() - 1 });

		while (!st.empty()) {
			auto tmp = st.top(); st.pop();
			int l = tmp.first;
			int r = tmp.second;

			int p = partition(v, l, r);
			if (p > l) st.push({ l, p - 1 });
			if (p < r) st.push({ p + 1, r });
		}
	}

	void quickSort2(vector<int>& v)
	{
		stack<pair<int, int>> st;
		st.push({ 0,v.size() - 1 });

		while (!st.empty()) {
			auto tmp = st.top(); st.pop();
			int l = tmp.first;
			int r = tmp.second;

			int p = partition(v, l, r);
			if (p < r) st.push({ p + 1, r });
			if (p > l) st.push({ l, p - 1 });
		}
	}

	int partition(vector<int>& v, int l, int r)
	{
		int pivot = v[r];
		int i = l;
		for (int j = l; j < r; j++) {
			if (v[j] < pivot) swap(v[j], v[i++]);
		}
		swap(v[i], v[r]);

		return i;
	}
};