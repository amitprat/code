#pragma once
#include "../Header.h"

class MaxIntervalOverlap
{
public:
	static void test() {
		vector<Interval> intervals = { {1,4},{2,5},{9,12},{5,9},{5,12} };

		cout << "Input: " << to_string(intervals) << endl;
		pair<int, Interval> res = findMaxIntervalOverlap(intervals);
		cout << "Output: " << res.first << ", " << res.second.to_string() << endl;

		cout << "Input: " << to_string(intervals) << endl;
		pair<int, Interval> res2 = findMaxIntervalOverlap2(intervals);
		cout << "Output: " << res2.first << ", " << res2.second.to_string() << endl;
	}

	static pair<int, Interval> findMaxIntervalOverlap(vector<Interval> intervals) {
		vector<int> startTimes;
		vector<int> endTimes;

		for (auto& interval : intervals) {
			startTimes.push_back(interval.start);
			endTimes.push_back(interval.end);
		}

		sort(startTimes.begin(), startTimes.end());
		sort(endTimes.begin(), endTimes.end());

		int i = 0, j = 0;
		int mxOverlap = 0;
		Interval maxInterval;

		while (i < startTimes.size() && j < endTimes.size()) {
			if (startTimes[i] <= endTimes[j]) i++;
			else {
				if (i - j > mxOverlap) {
					mxOverlap = i - j;
					maxInterval = { startTimes[i - 1], endTimes[j] };
				}
				j++;
			}
		}

		return { mxOverlap , maxInterval };
	}

	static pair<int, Interval> findMaxIntervalOverlap2(vector<Interval> intervals) {
		vector<pair<int, char>> sortedSet;
		for (auto& interval : intervals) {
			sortedSet.push_back({ interval.start, 's' });
			sortedSet.push_back({ interval.end, 'e' });
		}

		sort(sortedSet.begin(), sortedSet.end(), [](const auto& f, const auto& s) {
			if (f.first < s.first) return true;
			if (f.first > s.first) return false;
			return f.second > s.second;
			});

		int mxOverlap = 0, curOverlap = 0;
		Interval maxInterval;
		for (int i = 0; i < sortedSet.size(); i++) {
			if (sortedSet[i].second == 's') curOverlap++;
			else if (sortedSet[i].second == 'e') {
				if (curOverlap > mxOverlap) {
					mxOverlap = curOverlap;

					maxInterval = { sortedSet[i - 1].first,sortedSet[i].first };
				}
				curOverlap--;
			}
		}

		return { mxOverlap , maxInterval };
	}
};