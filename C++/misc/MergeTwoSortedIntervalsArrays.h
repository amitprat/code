#pragma once
#include "../Header.h"
using namespace std;

class MergeTwoSortedIntervalsArrays
{
public:
    static void test()
    {
        vector<Interval> v1 = { {1, 5} ,{10, 14},{16, 18} };
        vector<Interval> v2 = { {2, 6} ,{8, 10},{11, 20} };

        MergeTwoSortedIntervalsArrays obj;
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        cout << "Interval Set1: " << to_string(v1) << endl;
        cout << "Interval Set2: " << to_string(v2) << endl;

        vector<Interval> output = obj.merge(v1, v2);
        cout << "Interval Output Set: " << to_string(output) << endl;
    }

    vector<Interval> merge(vector<Interval> v1, vector<Interval> v2)
    {
        vector<Interval> result;
        int i = 0, j = 0;
        while (i < v1.size() || j < v2.size()) {
            if (i == v1.size()) mergeToResult(result, v2[j++]);
            else if (j == v2.size()) mergeToResult(result, v1[i++]);
            else {
                if (v1[i].start < v2[j].start) mergeToResult(result, v1[i++]);
                else mergeToResult(result, v2[j++]);
            }
        }

        return result;
    }

private:
    void mergeToResult(vector<Interval>& result, Interval interval)
    {
        if (result.empty() || interval.start > result.back().end) result.push_back(interval);
        else {
            interval = merge(result.back(), interval);
            result.pop_back();
            result.push_back(interval);
        }
    }

    Interval merge(Interval i1, Interval i2)
    {
        return { min(i1.start, i2.start), max(i1.end, i2.end) };
    }
};