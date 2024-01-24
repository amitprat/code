#pragma once
#include "../header.h"

class InsertIntervalInSortedIntervalSet
{
public:
    static void test()
    {
        InsertIntervalInSortedIntervalSet obj;

        {
            vector<Interval> intervals = {};
            Interval insert = { 10,11 };
            vector<Interval> expected = { {10,11} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;

        {
            vector<Interval> intervals = { {2, 3} };
            Interval insert = { 0,1 };
            vector<Interval> expected = { {0,1},{2,3} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;

        {
            vector<Interval> intervals = { {2, 3} };
            Interval insert = { 10,11 };
            vector<Interval> expected = { {2,3},{10,11} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;

        {
            vector<Interval> intervals = { {2, 3} };
            Interval insert = { 0,11 };
            vector<Interval> expected = { {0,11} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;

        {
            vector<Interval> intervals = { {2, 3},{6, 9} };
            Interval insert = { 0,11 };
            vector<Interval> expected = { {0,11} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;

        {
            vector<Interval> intervals = { {2, 3},{6, 9},{10,11} };
            Interval insert = { 3,9 };
            vector<Interval> expected = { {2,9},{10,11} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;

        {
            vector<Interval> intervals = { {0, 1},{6, 9} };
            Interval insert = { 2,3 };
            vector<Interval> expected = { {0,1},{2,3}, {6,9} };
            cout << "Input: set " << to_string(intervals) << ", " << insert.to_string() << endl;

            sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {return a.start <= b.start; });
            auto output = obj.insertInterval(intervals, insert);
            cout << "Output: set " << to_string(output) << endl;
            cout << "Expected: " << to_string(expected) << endl;
        }
        cout << endl;
    }

    vector<Interval> insertInterval(vector<Interval>& intervals, Interval interval) {
        if (intervals.empty()) {
            intervals.push_back(interval);
            return intervals;
        }

        int l = 0, r = intervals.size() - 1;
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (intervals[m].start > interval.start) r = m - 1;
            else l = m;
        }
        if (isOverlap(intervals, l, interval)) merge(intervals, l, interval);
        else {
            if (interval.start > intervals[l].end) l += 1;
            intervals.insert(intervals.begin() + l, interval);
        }

        return intervals;
    }

    bool isOverlap(vector<Interval>& intervals, int pos, Interval& next) {
        auto cur = intervals[pos];
        return (next.start >= cur.start && next.end <= cur.end) || (cur.start >= next.start && cur.end <= next.end);
    }

    void merge(vector<Interval>& intervals, int pos, Interval& next) {
        intervals[pos].start = min(intervals[pos].start, next.start);
        intervals[pos].end = max(intervals[pos].end, next.end);

        auto i = pos + 1;
        while (i < intervals.size() && intervals[i].start <= intervals[pos].end) {
            intervals[pos].start = min(intervals[pos].start, intervals[i].start);
            intervals[pos].end = max(intervals[pos].end, intervals[i].start);
            intervals.erase(intervals.begin() + i);
        }
    }
};