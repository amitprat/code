#pragma once
#include "../Header.h"

class MergeIntervals {
public:
	static void test() {
		{
			vector<Interval> it1 = { {1, 2},{3, 9} };
			vector<Interval> it2 = { {4, 5},{8, 10},{11, 12} };

			auto res = merge1(it1, it2);
			cout << format("Merged result of it1={} and it2={} is {}", to_string(it1), to_string(it2), to_string(res)) << endl;
		}

		{
			vector<Interval> it1 = { {1, 20},{3, 9} };
			vector<Interval> it2 = { {4, 5},{8, 10},{11, 12} };

			auto res = merge1(it1, it2);
			cout << format("Merged result of it1={} and it2={} is {}", to_string(it1), to_string(it2), to_string(res)) << endl;
		}
	}

	static vector<Interval> merge(vector<Interval>& it1, vector<Interval>& it2)
	{
		vector<Interval> result;
		int i = 0, j = 0;
		while (i < it1.size() || j < it2.size()) {
			if (i == it1.size()) {
				merge(result, it2[j++]);
			}
			else if (j == it2.size()) {
				merge(result, it1[i++]);
			}
			else {
				if (less(it1[i], it2[j])) {
					merge(result, it1[i++]);
				}
				else {
					merge(result, it2[j++]);
				}
			}
		}

		return result;
	}

	static void merge(vector<Interval>& result, Interval it)
	{
		if (result.empty() || it.start > result.back().end) {
			result.push_back(it);
		}
		else {
			result[result.size() - 1] = { min(result.back().start, it.start), max(result.back().end, it.end) };
		}
	}

	static bool less(Interval it1, Interval it2) {
		return it1.start <= it2.start;
	}

	static vector<Interval> merge1(vector<Interval>& it1, vector<Interval>& it2) {
		int n = it1.size();
		int m = it2.size();
		vector<Interval> result;

		int i = 0, j = 0;
		while (i < n || j < m) {
			if (i == n) merge1(result, it2[j++]);
			else if (j == m) merge1(result, it1[i++]);
			else if (it1[i].start <= it2[j].start) merge1(result, it1[i++]);
			else merge1(result, it2[j++]);
		}

		return result;
	}

	static void merge1(vector<Interval>& result, Interval it) {
		if (result.empty() || result.back().end < it.start) result.push_back(it);
		else {
			int n = result.size();
			result[n - 1] = { min(result[n - 1].start, it.start), max(result[n - 1].end, it.end) };
		}
	}
};