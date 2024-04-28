#pragma once
#include "../header.h"

/*
https://www.geeksforgeeks.org/find-intersection-of-intervals-given-by-two-lists/#

Given two 2-D arrays which represent intervals. Each 2-D array represents a list of intervals.
Each list of intervals is disjoint and sorted in increasing order. Find the intersection or set
of ranges that are common to both the lists.

Input:
arr1[][] = {{0, 4}, {5, 10}, {13, 20}, {24, 25}}
arr2[][] = {{1, 5}, {8, 12}, {15, 24}, {25, 26}}
Output: {{1, 4}, {5, 5}, {8, 10}, {15, 20}, {24, 24}, {25, 25}}

*/

class IntersectionOfSortedArrInterval {
   public:
    static void test() {
        IntersectionOfSortedArrInterval obj;

        {
            vector<Interval> v1 = {{1, 20}, {5, 7}, {10, 18}, {21, 50}};
            vector<Interval> v2 = {{2, 60}, {9, 11}, {11, 14}, {15, 25}, {30, 51}, {55, 100}};
            vector<Interval> res = {{5, 6}, {10, 14}, {15, 18}, {21, 25}, {30, 50}};

            auto curRes = obj.mergeSortedIntervals(v1, v2);
            for (int i = 0; i < curRes.size(); i++) {
                cout << curRes[i].to_string() << " ";
                assert(res[i] == curRes[i]);
            }
        }

        {
            vector<Interval> v1 = {{1, 2}, {5, 7}, {10, 18}, {21, 50}};
            vector<Interval> v2 = {{2, 6}, {9, 11}, {11, 14}, {15, 25}, {30, 51}, {55, 100}};
            vector<Interval> res = {{5, 6}, {10, 14}, {15, 18}, {21, 25}, {30, 50}};

            auto curRes = obj.mergeSortedIntervals2(v1, v2);
            for (int i = 0; i < curRes.size(); i++) {
                cout << curRes[i].to_string() << " ";
                assert(res[i] == curRes[i]);
            }
        }
    }

   private:
    vector<Interval> mergeSortedIntervals(vector<Interval>& v1, vector<Interval>& v2) {
        vector<Interval> result;

        int i = 0, j = 0;
        while (i < v1.size() && j < v2.size()) {
            if (!isOverlap(v1[i], v2[j])) {
                if (v1[i].start <= v2[j].start) {
                    addToResult(result, v1[i++]);
                } else {
                    addToResult(result, v2[j++]);
                }
            } else {
                result.push_back({max(v1[i].start, v2[j].start), min(v1[i].end, v2[j].end)});
                if (v1[i].end <= v2[j].end)
                    i++;
                else
                    j++;
            }
        }

        return result;
    }

    static void addToResult(vector<Interval>& result, Interval it) {
        if (result.empty() || !isOverlap(result.back(), it))
            result.push_back(it);
        else {
            Interval v1 = result.back();
            result.pop_back();

            if (it.end <= v1.end) return;

            result.push_back({it.end + 1, v1.end});
        }
    }

    static bool isOverlap(Interval it1, Interval it2) {
        return !(it1.start > it2.end || it2.start > it1.end);
    }

   private:
    vector<Interval> mergeSortedIntervals2(vector<Interval>& it1, vector<Interval>& it2) {
        int i = 0, j = 0, n = it1.size(), m = it2.size();

        vector<Interval> result;
        while (i < n && j < m) {
            int l = max(it1[i].start, it2[j].start);
            int r = min(it1[i].end, it2[j].end);

            if (l <= r) {
                result.push_back({l, r});
            }

            if (it1[i].end < it2[j].end) {
                i++;
            } else {
                j++;
            }
        }
    }
};