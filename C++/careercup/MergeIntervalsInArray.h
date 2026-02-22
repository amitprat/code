#pragma once
#include "../header.h"

/*
Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].
*/

class MergeIntervalsInArray {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> result;
        sort(intervals.begin(), intervals.end(), [](auto& f, auto& s) { return f[0] < s[0]; });
        for (auto& it : intervals) {
            if (result.empty() || !overlap(result.back(), it)) {
                result.push_back(it);
            } else {
                merge(result.back(), it);
            }
        }

        return result;
    }

    bool overlap(vector<int>& it1, vector<int>& it2) {
        return !(it1[1] < it2[0] || it2[1] < it1[0]);
    }

    void merge(vector<int>& it, vector<int>& it1) {
        it[0] = min(it[0], it1[0]);
        it[1] = max(it[1], it1[1]);
    }
};