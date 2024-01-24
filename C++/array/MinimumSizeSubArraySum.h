#pragma once
#include "../header.h"

class MinimumSizeSubArraySum {
public:
	static void test() {
		MinimumSizeSubArraySum obj;
		vector<pair<vector<int>, int>> tests = {
			{{2,3,1,2,4,3},-10},
			{{2,3,1,2,4,3},-1},
			{{2,3,1,2,4,3},0},
			{{2,3,1,2,4,3},1},
			{{2,3,1,2,4,3},2},
			{{2,3,1,2,4,3},3},
			{{2,3,1,2,4,3},4},
			{{2,3,1,2,4,3},5},
			{{2,3,1,2,4,3},6},
			{{2,3,1,2,4,3},7},
			{{2,3,1,2,4,3},8},
			{{2,3,1,2,4,3},9},
			{{2,3,1,2,4,3},10},
			{{2,3,1,2,4,3},45}
		};
		for (auto& test : tests) {
			auto res = obj.getMinimumSizeSubArray(test.first, test.second);
			cout << "MinLengthSubarray for sum:" << setw(3) << test.second << " :: (" << res.second.first << "," << res.second.second << ") = " << res.first;

			if (res.second.first != INT_MIN) {
				cout << to_string(test.first, res.second.first, res.second.second) << endl;
			}
			cout << endl;
		}
	}

	pair<int, pair<int, int>> getMinimumSizeSubArray(vector<int>& a, int s) {
		int l = 0, r = 0;
		pair<int, pair<int, int>> result = { 0,{INT_MIN, INT_MAX} };
		int curSum = 0;
		while (l < a.size()) {
			if (curSum >= s && l < r) {
				if (curSum < result.first) result = { curSum, {l,r - 1} };
				else if (r - l - 1 < result.second.second - result.second.first) result = { curSum, {l,r - 1} };
				curSum -= a[l++];
			}
			else {
				if (l > r) r++;
				if (r >= a.size()) break;
				curSum += a[r++];
			}
		}

		return result;
	}
};