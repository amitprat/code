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
#include <mutex>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class TotalTimeCoveredByIntervals
{
private:
public:
    static void test(vector<pair<int, int>> v)
    {
        TotalTimeCoveredByIntervals obj;
        cout << "Total Time: " << obj.totalTime(v) << endl;
    }

    int totalTime(vector<pair<int, int>> v) {
        sort(v.begin(), v.end(), [](auto& f, auto& s) {return f < s; });
        int total = 0;
        int last = INT_MIN;

        for (auto p : v) {
            total += max(p.second - max(last, p.first), 0);
            last = max(last, p.second);
            /*if (p.first < last) { total += max(p.second - last, 0); }
            else {
                total += p.second - p.first;
                last = p.second;
            }*/
        }

        return total;
    }
};