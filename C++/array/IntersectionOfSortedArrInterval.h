#pragma once
#include "../header.h"
using namespace std;

class IntersectionOfSortedArrInterval
{
public:
	static void test()
	{
		IntersectionOfSortedArrInterval obj;

		{
			vector<Interval> v1 = { {1,20},{5,7},{10,18},{21,50} };
			vector<Interval> v2 = { {2,60},{9,11},{11,14}, {15,25},{30,51},{55,100} };
			vector<Interval> res = { {5,6},{10,14},{15,18},{21,25},{30,50} };

			auto curRes = obj.findIntersection2(v1, v2);
			for (int i = 0; i < curRes.size(); i++) {
				cout << curRes[i].to_string() << " ";
				assert(res[i] == curRes[i]);
			}
		}

		{
			vector<Interval> v1 = { {1,2},{5,7},{10,18},{21,50} };
			vector<Interval> v2 = { {2,6},{9,11},{11,14}, {15,25},{30,51},{55,100} };
			vector<Interval> res = { {5,6},{10,14},{15,18},{21,25},{30,50} };

			auto curRes = obj.findIntersection2(v1, v2);
			for (int i = 0; i < curRes.size(); i++) {
				cout << curRes[i].to_string() << " ";
				assert(res[i] == curRes[i]);
			}
		}
	}

	vector<Interval> findIntersection(vector<Interval> v1, vector<Interval> v2) {
		vector<Interval> res;
		int i = 0, j = 0;

		while (i < v1.size() && j < v2.size()) {
			Interval mergedIntervalV1 = v1[i];
			int k = i;
			while (k < v1.size() - 1 && v1[k].end == v1[k + 1].start) { mergedIntervalV1.end = v1[k + 1].end; k++; }

			Interval mergedIntervalV2 = v2[j];
			k = j;
			while (k < v2.size() - 1 && v2[k].end == v2[k + 1].start) { mergedIntervalV2.end = v2[k + 1].end; k++; }

			if (mergedIntervalV1.start >= mergedIntervalV2.end) j++;
			else if (mergedIntervalV2.start >= mergedIntervalV1.end) i++;
			else {
				int mn = max(mergedIntervalV1.start, mergedIntervalV2.start);
				int mx = min(mergedIntervalV1.end, mergedIntervalV2.end);
				res.push_back({ mn, mx });
				if (mx == mergedIntervalV1.end) i++;
				else if (mx == mergedIntervalV2.end) j++;
			}
		}
		return res;
	}

	vector<Interval> findIntersection2(vector<Interval>& v1, vector<Interval>& v2) {
		vector<Interval> result;

		int i = 0, j = 0;
		while (i < v1.size() && j < v2.size()) {
			if (!isOverlap(v1[i], v2[j])) {
				if (v1[i].start <= v2[j].start) {
					addToResult(result, v1[i++]);
				}
				else {
					addToResult(result, v2[j++]);
				}
			}
			else {
				result.push_back({ max(v1[i].start,v2[j].start),min(v1[i].end,v2[j].end) });
				if (v1[i].end <= v2[j].end) i++;
				else j++;
			}
		}

		return result;
	}

	static void addToResult(vector<Interval>& result, Interval it) {
		if (result.empty() || !isOverlap(result.back(), it)) result.push_back(it);
		else {
			Interval v1 = result.back();
			result.pop_back();
			if (it.end <= v1.end) return;
			result.push_back({ it.end + 1,v1.end });
		}
	}

	static bool isOverlap(Interval it1, Interval it2) {
		return !(it1.start > it2.end || it2.start > it1.end);
	}
};