#pragma once
#include "../Header.h"

class MaxProfitCarRental {
public:
	static void test() {
		MaxProfitCarRental obj;
		vector<pair<int, int>> arr = { {1, 10}, {5, 8}, {4, 14}, {8,16} };
		vector<int> price = { 100, 99, 101, 50 };
		cout << obj.maxProfit(arr, price) << endl;
	}

	int maxProfit(vector<pair<int, int>> arr, vector<int> price) {
		auto res1 = maxProfitDP(arr, price);
		auto res2 = maxProfitRecMemoization(arr, price);

		assert(res1 == res2);

		return res1;
	}

	int maxProfitDP(vector<pair<int, int>> arr, vector<int> price) {
		int n = arr.size();
		vector<tuple<int, int, int>> tuples;

		for (int i = 0; i < n; i++) {
			tuples.push_back({ arr[i].first,arr[i].second,price[i] });
		}
		sort(tuples.begin(), tuples.end(), [](auto f, auto s) {return get<1>(f) < get<1>(s); });

		vector<int> mxProfit(n);
		for (int i = 0; i < n; i++) {
			int curMax = get<2>(tuples[i]);
			for (int j = i - 1; j >= 0; j--) {
				if (get<1>(tuples[j]) <= get<0>(tuples[i])) {
					curMax = max(curMax, mxProfit[j] + get<2>(tuples[i]));
				}
			}
			mxProfit[i] = curMax;
		}

		return *max_element(mxProfit.begin(), mxProfit.end());
	}

	int maxProfitRecMemoization(vector<pair<int, int>> arr, vector<int> price) {
		vector<int> memo(price.size(), 0);
		return maxProfitRecMemoization(arr, price, price.size(), { -1,-1 }, memo);
	}

	int maxProfitRecMemoization(vector<pair<int, int>> arr, vector<int> price, int n, pair<int, int> prev, vector<int>& memo) {
		if (n == 0) return 0;
		if (overlap(prev, arr[n - 1])) return maxProfitRecMemoization(arr, price, n - 1, prev, memo);
		if (memo[n - 1] > 0) return memo[n - 1];
		memo[n - 1] = max(
			maxProfitRecMemoization(arr, price, n - 1, prev, memo),
			price[n - 1] + maxProfitRecMemoization(arr, price, n - 1, arr[n - 1], memo)
		);
		return memo[n - 1];
	}
	bool overlap(pair<int, int> f, pair<int, int> s) {
		return !(f.second <= s.first || s.second <= f.first);
	}
};