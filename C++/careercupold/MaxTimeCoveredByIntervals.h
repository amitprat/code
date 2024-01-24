#pragma once
#include "../Header.h"

/*
Given a list of arrays of time intervals, write a function that calculates the total amount of time covered by the intervals.
For example:
input = [(1,4), (2,3)]
return 3
input = [(4,6), (1,2)]
return 3
input = {{1,4}, {6,8}, {2,4}, {7,9}, {10, 15}}
return 11

public static int mergeSegments(int[][] segments) {
		Arrays.sort(segments, (x, y) -> x[0] - y[0]);

		int result = 0;
		int last = 0;
		for(int[] seg : segments) {
			result += Math.max(seg[1] - Math.max(last, seg[0]), 0);
			last = Math.max(last, seg[1]);
		}
		return result;
	}
*/
class TotalTimeCoveredByIntervals {
public:
	static void test() {
		TotalTimeCoveredByIntervals obj;

		{
			vector<pair<int, int>> input = { {1,4}, {2,3} };
			auto res = obj.maxTimeConvered(input);
			cout << format("Total time covered by intervals for input={} is {}", to_string(input), res) << endl;
		}

		{
			vector<pair<int, int>> input = { {4,6}, {1,2} };
			auto res = obj.maxTimeConvered(input);
			cout << format("Total time covered by intervals for input={} is {}", to_string(input), res) << endl;
		}

		{
			vector<pair<int, int>> input = { {1,4}, {6,8}, {2,4}, {7,9}, {10, 15} };
			auto res = obj.maxTimeConvered(input);
			cout << format("Total time covered by intervals for input={} is {}", to_string(input), res) << endl;
		}

		{
			vector<pair<int, int>> input = { {1,4}, {2,3}, {2,6} };
			auto res = obj.maxTimeConvered(input);
			cout << format("Total time covered by intervals for input={} is {}", to_string(input), res) << endl;
		}
	}

	int maxTimeConvered(vector<pair<int, int>> input) {
		auto res1 = maxTimeConvered1(input);

		return res1;
	}

	int maxTimeConvered1(vector<pair<int, int>> input) {
		sort(input.begin(), input.end(), [](const auto& f, const auto& s) {return f.first < s.first; });

		int result = 0;
		int lastEnd = 0;
		for (int i = 0; i < input.size(); i++) {
			int curStart = max(input[i].first, lastEnd); // {(1,4), (2,3), (2,6)} -> curStart: {1, 4, 4}
			result += max(input[i].second - curStart, 0); // curEnd - curStart -> {3, max(-1,0), 2}
			lastEnd = max(input[i].second, lastEnd); // update lastEnd to max of current end or lastEnd
		}
		return result;
	}
};