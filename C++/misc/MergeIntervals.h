#pragma once
#include "../header.h"

class MergeInterval {
public:
    static void test() {
        MergeInterval obj;

        {
            vector<Interval> intervals = {
                {-10,-1},
                {0,2},
                {4,10}
            };
            Interval toInsert = { -5,1 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }

        cout << endl << endl;
        {
            vector<Interval> intervals = {
                {-10,-1},
                {0,2},
                {4,10}
            };
            Interval toInsert = { -20,-2 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }

        cout << endl << endl;
        {
            vector<Interval> intervals = {
                {-10,-1},
                {0,2},
                {4,10}
            };
            Interval toInsert = { -20,-11 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }

        cout << endl << endl;
        {
            vector<Interval> intervals = {
                {-10,-1},
                {0,2},
                {4,10}
            };
            Interval toInsert = { 11,20 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }

        cout << endl << endl;
        {
            vector<Interval> intervals = {
                {-10,-1},
                {0,2},
                {4,10}
            };
            Interval toInsert = { 1,1 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }

        cout << endl << endl;
        {
            vector<Interval> intervals = {
                {-10,-1},
                {2,3},
                {4,10}
            };
            Interval toInsert = { 1,1 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }

        cout << endl << endl;
        {
            vector<Interval> intervals = {
                {-10,-1},
                {2,3},
                {4,10}
            };
            Interval toInsert = { -20,20 };

            cout << to_string(intervals) << endl;

            obj.merge(intervals, toInsert);

            cout << to_string(intervals) << endl;
        }
    }

    void merge(vector<Interval>& in, Interval item) {
        int index = 0;
        for (auto it = in.begin(); it != in.end();) {
            if (item < *it) {
                break;
            }

            if (it->overlap(item)) {
                item.start = min(it->start, item.start);
                item.end = max(it->end, item.end);
                it = in.erase(it);
            }
            else {
                it++;
                index++;
            }
        }
        in.insert(in.begin() + index, item);
    }
};