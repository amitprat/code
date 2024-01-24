#pragma once
#include "../Header.h"

class MinimumPerfectSquares {
public:
	static void test() {
		int n = 12;
		vector<int> dp(n + 1, -1);
		int cnt = minPerfectSquares(n, dp);
		cout << format("Minimum number of perfect squares {} needed to reach target sum {}", cnt, n) << endl;
	}

	static int minPerfectSquares(int n, vector<int>& dp) {
		if (n < 0) return INT_MAX;
		if (n == 0) return 0;
		if (dp[n] != -1) return dp[n];

		int i = 1;
		int cur = INT_MAX;
		while (i * i <= n) {
			int val = minPerfectSquares(n - i * i, dp);
			if (val != INT_MAX) cur = min(cur, val + 1);
			i++;
		}

		dp[n] = cur;

		return dp[n];
	}
};