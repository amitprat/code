#pragma once
#include "../header.h"

class InsertIntervalInSortedIntervalArray {
   public:
    vector<vector<int>> insert1(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        for (auto& it : intervals) {
            if (newInterval[1] < it[0]) {
                result.push_back(newInterval);
                newInterval = it;
            } else if (newInterval[0] > it[1]) {
                result.push_back(it);
            } else {
                newInterval = {min(it[0], newInterval[0]), max(it[1], newInterval[1])};
            }
        }

        result.push_back(newInterval);
        return result;
    }

    vector<vector<int>> insert2(vector<vector<int>>& intervals, vector<int>& newInterval) {
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end(), [](const auto& f, const auto& s) {
            return f[0] < s[0];
        });

        int i = 0;
        for (int j = 1; j < intervals.size(); j++) {
            if (intervals[i][1] < intervals[j][0]) i++;
            else {
                intervals[i] = {min(intervals[i][0], intervals[j][0]), max(intervals[i][1], intervals[j][1])};
            }
        }

        return {intervals.begin(), intervals.begin() + i};
    }
};