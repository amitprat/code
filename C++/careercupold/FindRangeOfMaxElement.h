#pragma once
#include "../Header.h"

class FindRangeOfMaxElement {
public:
	static void test()
	{
		int arr[] = { 1,5,4,3,6 };
		int n = sizeof(arr) / sizeof(int);
		stack<pair<int, int>> st;

		for (int i = 1; i <= n; i++) {
			int prev = i;
			while (!st.empty() && st.top().first <= arr[i - 1]) {
				cout << st.top().first << " " << st.top().second << "," << i - 1 << endl;
				prev = st.top().second;
				st.pop();
			}
			st.push({ arr[i - 1],prev });
		}

		while (!st.empty()) {
			cout << st.top().first << " " << st.top().second << "," << n << endl;
			st.pop();
		}
	}
};