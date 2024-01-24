#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class MergeSortedIntervalsArr
{
public:
    using Interval = pair<int, int>;
    static void test(vector<Interval> v1, vector<Interval> v2)
    {
        MergeSortedIntervalsArr obj;
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        cout << "Interval Set1: ";
        for (auto i : v1) cout << "{" << i.first << ", " << i.second << "}, ";
        cout << endl;
        cout << "Interval Set2: ";
        for (auto i : v2) cout << "{" << i.first << ", " << i.second << "}, ";
        cout << endl;

        vector<Interval> output = obj.merge(v1, v2);
        cout << "Interval Output Set: ";
        for (auto i : output) cout << "{" << i.first << ", " << i.second << "}, ";
        cout << endl;
    }

    vector<Interval> merge(vector<Interval> v1, vector<Interval> v2)
    {
        vector<Interval> result;
        int i = 0, j = 0;
        while (i < v1.size() || j < v2.size()) {
            if (i == v1.size()) mergeToResult(result, v2[j++]);
            else if (j == v2.size()) mergeToResult(result, v1[i++]);
            else {
                if (v1[i].first < v2[j].first) mergeToResult(result, v1[i++]);
                else mergeToResult(result, v2[j++]);
            }
        }

        return result;
    }

private:
    void mergeToResult(vector<Interval>& result, Interval interval)
    {
        if (result.empty() || interval.first > result.back().second) result.push_back(interval);
        else {
            interval = merge(result.back(), interval);
            result.pop_back();
            result.push_back(interval);
        }
    }

    Interval merge(Interval i1, Interval i2)
    {
        return { min(i1.first, i2.first), max(i1.second, i2.second) };
    }
};