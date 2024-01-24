#pragma once
#include "../Header.h"

class SpecialKeyboard
{
public:
	static void test() {
		vector<int> tests = { 3,7,8,9 };
		for (auto t : tests) {
			cout << "Max characters = " << maxChars(t) << endl;
		}
	}

	static int maxChars(int n) {
		if (n <= 6) return n;

		int* memo = new int[n + 1];
		for (int i = 0; i <= 6; i++) memo[i] = i;

		for (int i = 7; i <= n; i++) {
			memo[i] = i;
			for (int j = i - 3; j >= 1; j--) {
				int cur = (i - j - 1) * memo[j];
				memo[i] = max(memo[i], cur);
			}
		}

		return memo[n];
	}
};