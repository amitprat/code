#pragma once
#include "../Header.h"

class MinimumLengthSeq {
public:
	static void test() {
		MinimumLengthSeq obj;

		{
			vector<int> arr = { 2, 1, 1, 4, 3, 6 };
			int sum = 8;

			auto res = obj.findMinLen(arr, sum);
			cout << to_string(res) << endl;
		}

		{
			vector<int> arr = { 2, 1, 10, 4, 3, 6 };
			int sum = 8;

			auto res = obj.findMinLen(arr, sum);
			cout << to_string(res) << endl;
		}
	}

	vector<int> findMinLen(vector<int> arr, int sum) {
		int l = 0, r = 0, curSum = 0;
		pair<int, int> window = { -1,-1 };

		while (r < arr.size()) {
			curSum += arr[r];
			while (l <= r && curSum - arr[l] > sum) {
				curSum -= arr[l++];
			}

			if (curSum >= sum && (window.first == -1 || r - l < window.second - window.first)) {
				window = { l,r };
			}

			r++;
		}

		vector<int> response;
		if (window.first != -1) {
			for (int i = window.first; i <= window.second; i++) response.push_back(arr[i]);
		}

		return response;
	}
};