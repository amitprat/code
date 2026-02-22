#pragma once
#include "../header.h"

class EraseOverlappingIntervals {
   public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(), [](auto& f, auto& s) { return f[1] < s[1]; });
        int prev = intervals[0][1];
        int nonOverlapping = 1;
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= prev) {
                nonOverlapping++;
                prev = intervals[i][1];
            }
        }

        return intervals.size() - nonOverlapping;
    }
};