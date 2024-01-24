#pragma once
#include "../Header.h"

class MergeIntervals {
public:
    static void test() {
        vector<Interval> arr1 = { {1, 2},{3, 9} };
        vector<Interval> arr2 = { {4, 5},{8, 10},{11, 12} };

        auto res = merge(arr1, arr2);
        cout << to_string(res) << endl;
    }

    static vector<Interval> merge(vector<Interval>& arr1, vector<Interval>& arr2) {
        vector<Interval> result;
        int i = 0, j = 0;
        while (i < arr1.size() && j < arr2.size()) {
            if (arr1[i].start <= arr2[j].start) {
                mergeOrInsert(result, arr1[i]);
                i++;
            }
            else {
                mergeOrInsert(result, arr2[j]);
                j++;
            }
        }

        while (i < arr1.size()) { mergeOrInsert(result, arr1[i]); i++; }
        while (j < arr2.size()) { mergeOrInsert(result, arr2[j]); j++; }

        return result;
    }

private:
    static void mergeOrInsert(vector<Interval>& result, Interval& it) {
        if (result.empty() || it.start > result.back().end) result.push_back(it);
        else {
            int n = result.size() - 1;
            result[n].end = max(result[n].end, it.end);
        }
    }
};