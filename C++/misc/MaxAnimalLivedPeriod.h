/*
Input intervals (or lifetimes): [5, 11], [6, 18], [2, 5], [3,12]

1. Put the end and start times of the intervals in one array. Sort it!. Always put the start time before end time in case they are equal. Maintain flags to identify a start/end interval. For above input I'll do something like:
2S, 3S, 5S, 5E, 6S, 11E, 12E, 18E

2. Now scan the array from left to right keeping track of how many intervals we are in. (This would be equal to total numbers of start intervals - total number of end intervals encountered so far). For above input I'll get something like:
1, 2, 3, 2, 3, 2, 1, 0

3. Now pick the maxima points from step 2. All the maxima points will be Start intervals and the point next to a maxima point will always be an end interval (which will be the end of the maxima start interval). So we'll get:
[5S,5E] and [6S,11E].

Hence the result is [5,5], [6,11]
*/
#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class MaxAnimalLived
{
public:
    struct Interval {
        int start;
        int end;
        Interval(int start, int end) : start(start), end(end) {}
        string to_string() {
            return "{" + std::to_string(start) + ", " + std::to_string(end) + "}";
        }
    };
    static void test() {
        MaxAnimalLived obj;
        vector<Interval> intervals = {
            {5,11},{6,18},{2,5},{3,12}
        };

        {
            auto res = obj.findMaxPeriod(intervals);
            cout << "Max Period = " << res.first << ":" << res.second.to_string() << endl;
        }
        //vector<pair<int, Interval>> res = obj.findPeriod2(intervals);
        //for (auto r : res) {
        //    cout << r.first << ":" << r.second.to_string() << endl;
        //}
    }

    pair<int, Interval> findMaxPeriod(vector<Interval> intervals) {
        multimap<int, char> m;
        int period = 0;
        Interval curPeriod = { INT_MIN, INT_MAX };
        int mxPeriodCount = 0;
        Interval maxPeriod = curPeriod;

        for (auto interval : intervals) {
            m.insert({ interval.start, 'a' });
            m.insert({ interval.end, 'd' });
        }

        for (auto entry : m) {
            if (entry.second == 'a') {
                curPeriod.start = max(curPeriod.start, entry.first);
                period++;
            }
            else if (entry.second == 'd') {
                curPeriod.end = entry.first;
                if (period > mxPeriodCount) {
                    maxPeriod = curPeriod;
                    mxPeriodCount = period;
                }
                period--;
            }
        }
        mxPeriodCount = max(mxPeriodCount, period);

        return { mxPeriodCount, maxPeriod };
    }

    vector<pair<int, Interval>> findPeriod(vector<Interval> intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
        vector<pair<int, Interval>> result;
        Interval curMax = intervals[0];
        int curMaxCount = 1;
        result.push_back({ curMaxCount, curMax });
        int i = 0;
        int j = 1;

        while (j < intervals.size()) {
            auto cur = intervals[j];
            if (cur.start > intervals[i].end) {
                while (!result.empty() && curMaxCount > result.back().first) result.pop_back();
                result.push_back({ curMaxCount,curMax });
                curMaxCount--;
                i++;
            }
            else {
                curMaxCount++;
                curMax = { max(cur.start, curMax.start), min(cur.end, curMax.end) };
            }
            j++;
        }

        return result;
    }

    vector<pair<int, Interval>> findPeriod2(vector<Interval> intervals) {
        vector<pair<int, Interval>> result;
        vector<int> starts;
        vector<int> ends;
        for (auto i : intervals) {
            starts.push_back(i.start);
            ends.push_back(i.end);
        }

        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());

        int i = 0, j = 1;
        int curMaxCount = 1;
        Interval curMax = intervals[i];
        while (i < intervals.size() && j <= intervals.size()) {
            if (j < intervals.size() && starts[j] <= ends[i]) {
                curMax = { max(curMax.start, starts[j]), min(ends[i], curMax.end) };
                curMaxCount++;
                j++;
            }
            else {
                while (!result.empty() && curMaxCount > result.back().first) result.pop_back();
                if (result.empty() || curMaxCount == result.back().first) {
                    result.push_back({ curMaxCount,curMax });
                }
                curMaxCount--;
                i++;
                curMax.end = ends[i];
            }
        }

        return result;
    }
};