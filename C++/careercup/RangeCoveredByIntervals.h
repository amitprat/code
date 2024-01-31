#include "../header.h"

/*
https://www.careercup.com/question?id=4695029784248320

Given a list of tuples representing intervals, return the range these intervals
covered.
e.g:
[(1,3), (2,5),(8,9)] should return 5
*/
class RangeCoveredByIntervals {
   public:
    static void test() {
        RangeCoveredByIntervals obj;
        vector<vector<Interval>> intervals = {
            {{1, 3}, {2, 5}, {8, 9}},
            {{1, 2}, {1, 3}, {1, 4}, {1, 5}},
            {{1, 3}, {2, 5}, {8, 10}, {4, 9}}};

        for (auto& interval : intervals) {
            cout << interval << " : ";
            auto res1 = obj.range_covered(interval);
            auto res2 = obj.range_covered_alternative(interval);
            assert(res1 == res2);

            cout << res1 << endl;
        }
    }

   public:
    int range_covered(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& f, const auto& s) {
            return f.start < s.start;
        });

        int result = 0;
        int last = 0;

        for (auto& it : intervals) {
            if (last <= it.start) {
                result += (it.end - it.start);
            } else {
                // this interval completely lies within earlier interval and hence ignore it.
                if (it.end <= last) continue;

                result += it.end - last;
            }

            last = it.end;
        }

        return result;
    }

   public:
    int range_covered_alternative(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& f, const auto& s) {
            return f.start < s.start;
        });

        int range = 0;
        int i = 0;
        while (i < intervals.size()) {
            int e = intervals[i].end;

            // merge all the intervals which has start <= cur_end (i.e. overlap)
            // get the end as max of all as they all overlap.
            int j = i + 1;
            while (j < intervals.size() && e >= intervals[j].start) {
                e = max(e, intervals[j].end);
                j++;
            }

            range += e - intervals[i].start;

            // move i after all merged intervals
            i = j;
        }

        return range;
    }
};