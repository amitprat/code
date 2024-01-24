#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class Interval
{
public:
    int start;
    int end;
    string str() { return "{" + to_string(start) + "," + to_string(end) + "}"; }
};
class IntervalOverlap
{
public:
    vector<vector<Interval>> findOverlapping(vector<Interval> v)
    {
        vector<pair<pair<int, int>, bool>> tmp;
        int index = 0;
        for (auto& i : v) { tmp.push_back({ {i.start, index},false }); tmp.push_back({ {i.end, index}, true }); index++; }
        sort(tmp.begin(), tmp.end(), [](auto i, auto j) { return i.first.first < j.first.first || (i.first.first == j.first.first && !i.second); });

        vector<vector<Interval>> result;
        vector<int> cur;
        for (auto i : tmp) {
            if (!i.second) { cur.push_back(i.first.second); }
            else {
                vector<Interval> t;
                for (auto j : cur) {
                    t.push_back(v[j]);
                }

                if (t.size() > 1) result.push_back(t);
                cur.erase(std::remove(cur.begin(), cur.end(), i.first.second), cur.end());
            }
        }

        return result;
    }

    void tester()
    {
        vector<Interval> v = { {1,5},{2,3},{3,4},{6,7} };//{ {1,3},{12,14},{2,4},{13,15},{5,10} };
        auto result = findOverlapping(v);
        for (auto i : result)
        {
            for (auto j : i) cout << j.str() << " ";
            cout << endl;
        }
    }
};