#pragma once
#include "../Header.h"

class ShortestSubseqContainingSubarray {
public:
	static void test() {
		ShortestSubseqContainingSubarray obj;
		vector<int> sub = { 1, 5, 9 };
		vector<int> arr = { 7, 5, 9, 8, 2, 1, 3, 5, 7,9,1, 1, 5, 8, 8, 9, 7 };

		auto res = obj.findShortestSubsequence(arr, sub);
		if (res.first != -1) {
			cout << "Subarray exist from " << res.first << " to " << res.second << endl;
		}
	}

	pair<int, int> find(vector<int> arr, vector<int> sub) {
		unordered_map<int, int> arrhash, subhash;
		for (int i = 0; i < sub.size(); i++) subhash[sub[i]]++;
		int count = 0;
		int start = 0;
		pair<int, int> mx = { -1,999 };

		for (int i = 0; i < arr.size(); i++) {
			int e = arr[i];
			if (!subhash[e]) continue;

			arrhash[e]++;
			if (arrhash[e] <= subhash[e]) count++;

			if (count == sub.size()) {
				while (!subhash[arr[start]] || (arrhash[arr[start]] > arrhash[arr[start]])) start++;
				if ((i - start) < (mx.second - mx.first)) mx = { start, i };

				arrhash[arr[start++]]--;
				count--;
			}
		}

		return mx;
	}

	pair<int, int> findShortestSubsequence(vector<int>& arr, vector<int>& sub) {
		unordered_map<int, int> subCnt, arrCnt;

		for (auto e : sub) subCnt[e]++;

		pair<int, int> result = { INT_MIN, INT_MAX };
		int total = 0, start = 0;
		for (int i = 0; i < arr.size(); i++) {
			int e = arr[i];
			arrCnt[e]++;

			if (arrCnt[e] <= subCnt[e]) total++;

			if (total == sub.size()) {
				while (start <= i && arrCnt[arr[start]] > subCnt[arr[start]]) {
					arrCnt[arr[start]]--;
					start++;
				}

				if (result.first == INT_MIN || (result.second - result.first > i - start)) {
					result = { start, i };
				}

				arrCnt[arr[start]]--;
				start++;
				total--;
			}
		}

		return result;
	}
};