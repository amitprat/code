#pragma once
#include "../Header.h"

class GetMaximumPossibleInteger
{
public:
	static void test() {
		int num = 7899;
		auto res = getMaximumNum(num);
		cout << res << endl;
	}

	static int getMaximumNum(int num) {
		auto numVector = getNumVector(num);
		int mx = INT_MIN;
		getMaximum(numVector, 0, numVector.size(), mx, 2);

		return mx;
	}

	static void getMaximum(vector<int>& nums, int s, int n, int& mx, int k) {
		if (s == n || k == 0) {
			int cur = getNumFromVector(nums);
			mx = max(mx, cur);
			return;
		}

		for (int i = s; i < n; i++) {
			swap(nums[i], nums[s]);
			getMaximum(nums, s + 1, n, mx, k - (i != s));
			swap(nums[i], nums[s]);
		}
	}

	static vector<int> getNumVector(int num) {
		vector<int> res;
		while (num) {
			res.push_back(num % 10);
			num /= 10;
		}
		reverse(res.begin(), res.end());

		return res;
	}

	static int getNumFromVector(vector<int> nums) {
		int res = 0;
		for (auto num : nums) {
			res = res * 10 + num;
		}

		return res;
	}
};