#include "../header.h"

class MergeTwoSortedIntervalsArray {
   public:
    static void test() {
        MergeTwoSortedIntervalsArray obj;
        vector<Interval> arr1 = {{1, 2}, {3, 9}};
        vector<Interval> arr2 = {{4, 5}, {8, 10}, {11, 12}};
        obj.print(arr1);
        obj.print(arr2);

        auto out = obj.mergeArrays(arr1, arr2);
        obj.print(out);
    }

   private:
    vector<Interval> mergeArrays(vector<Interval>& arr1, vector<Interval>& arr2) {
        vector<Interval> output;
        int i = 0, j = 0;
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i].start <= arr2[j].start) {
                insertOrMerge(output, arr1[i]);
                i++;
            } else {
                insertOrMerge(output, arr2[j]);
                j++;
            }
        }

        while (i < arr1.size()) insertOrMerge(output, arr1[i++]);
        while (j < arr2.size()) insertOrMerge(output, arr2[j++]);

        return output;
    }

    void insertOrMerge(vector<Interval>& out, Interval it) {
        if (out.empty() || it.start > out.back().end) {
            out.push_back(it);
        } else {
            auto cur = out.back();
            out.pop_back();
            cur.start = min(cur.start, it.start);
            cur.end = max(cur.end, it.end);
            out.push_back(cur);
        }
    }

    void print(vector<Interval>& out) {
        for (auto& it : out) cout << it.to_string() << ",";
        cout << endl;
    }

   private:
    void mergeIntervalsInPlace(vector<Interval>& intervals) {
        int i = 0;
        for (int j = 1; j < intervals.size(); j++) {
            if (overlap(intervals[i], intervals[j])) {
                merge(intervals[i], intervals[j]);
            } else {
                i++;
                intervals[i] = intervals[j];
            }
        }

        while (intervals.size() > i + 1) intervals.pop_back();
    }

    bool overlap(Interval it1, Interval it2) {
        return it2.start <= it1.end && it2.start >= it1.start;
    }

    void merge(Interval& it1, Interval& it2) {
        it1 = {min(it1.start, it2.start), max(it1.end, it2.end)};
    }

   private:
    void mergeIntervalsInPlace2(vector<Interval>& intervals) {
        sort(intervals.begin(), intervals.end(), [](auto& f, auto& s) { return f.start < s.start; });

        vector<Interval> result;
        for (auto& interval : intervals) {
            if (result.empty() || result.back().end >= interval.start) {
                result.back().end = max(result.back().end, interval.end);
            }
        }

        return result;
    }
};