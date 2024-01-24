#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5103437989543936

There are many sorted arrays. Find a minimum range, so that in each array there's at least one integer within this range.
*/
class FindMinimumRange {
public:
	static void test() {
		vector<vector<int>> arrs = {
			{1,2,4,5,9},
			{3,4,5,6,7},
			{2,3,5,6,7},
			{1,5,8,9,9},
			{10,20,50,60,70}
		};

		pair<int, int> res = smallestRange(arrs);
		cout << to_string(res) << endl;
	}

	static pair<int, int> smallestRange(vector<vector<int>> arrs) {
		using  p = pair<int, pair<int, int>>;
		using v = vector<pair<int, pair<int, int>>>;
		priority_queue<p, v, std::greater<p>> pq;
		int mn = INT_MAX, mx = INT_MIN;

		for (int i = 0; i < arrs.size(); i++) {
			pq.push({ arrs[i][0], {i,0} });
			mn = min(mn, arrs[i][0]);
			mx = max(mx, arrs[i][0]);
		}

		pair<int, int> result = { mn, mx };

		while (true) {
			auto f = pq.top(); pq.pop();
			mn = f.first;
			mx = max(f.first, mx);

			if (mx - mn < result.second - result.first) {
				result = { mn, mx };
			}

			int arrIdx = f.second.first;
			int arrPos = f.second.second;
			if (arrPos < arrs[arrIdx].size() - 1) {
				arrPos++;
				pq.push({ arrs[arrIdx][arrPos], {arrIdx, arrPos} });
			}
			else {
				break;
			}
		}

		return result;
	}
};