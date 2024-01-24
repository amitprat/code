#pragma once
#include "../Header.h"

class MergeIntervals {
public:
    static void test() {
        MergeIntervals obj;
        vector<Interval> arr1 = { Interval{3,19},Interval{4,8}, Interval{17,25},Interval{20,45}, Interval{58,73} };
        vector<Interval> arr2 = { Interval{6,18},Interval{7,9},Interval{8,27}, Interval{40,47} };

        vector<Interval> res = obj.merge1(arr1, arr2);

        cout << to_string(res);
    }

    bool overlap(Interval prev, Interval next) {
        bool notOverlap = prev.end < next.start || prev.start > next.end;
        return !notOverlap;
    }

    vector<Interval> merge1(vector<Interval> arr1, vector<Interval> arr2) {
        vector<Interval> result;
        Interval prev = { -1,-1 };
        int i = 0, j = 0;
        while (i < arr1.size() || j < arr2.size()) {
            Interval smallest = { -1,-1 };
            if (i < arr1.size() && j < arr2.size() && arr1[i].start <= arr2[j].start) {
                smallest = arr1[i++];
            }
            else if (j < arr2.size()) {
                smallest = arr2[j++];
            }
            else {
                smallest = arr1[i++];
            }
            if (prev.start == -1) prev = smallest;
            else if (overlap(prev, smallest)) prev = { min(prev.start,smallest.start),max(prev.end,smallest.end) };
            else {
                result.push_back(prev);
                prev = smallest;
            }
        }
        if (prev.start != -1) result.push_back(prev);

        return result;
    }

    vector<Interval> merge(vector<Interval> arr1, vector<Interval> arr2) {
        vector<Interval> result;
        stack<int> st;
        vector<pair<int, bool>> values;
        for (auto s : arr1) {
            values.push_back({ s.start,true });
            values.push_back({ s.end,false });
        }

        for (auto s : arr2) {
            values.push_back({ s.start,true });
            values.push_back({ s.end,false });
        }

        sort(values.begin(), values.end(), [](const auto& first, const auto& second) {return first.first <= second.first; });

        for (auto val : values) {
            if (val.second) st.push(val.first);
            else {
                auto top = st.top(); st.pop();
                if (st.empty()) {
                    result.push_back({ top,val.first });
                }
            }
        }

        return result;
    }
};