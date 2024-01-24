#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class Schedule
{
public:
    int arrival;
    int departure;
    Schedule(int arrival, int departure) : arrival(arrival), departure(departure) {}
    string str() {
        return "{" + to_string(arrival) + ", " + to_string(departure) + "}";
    }
};

class StationTimeChart
{
public:
    vector<Schedule> schedules;

public:
    StationTimeChart(vector<pair<int, int>>& schedules) {
        for (auto s : schedules) {
            this->schedules.push_back(Schedule(s.first, s.second));
        }
    }
    string str() {
        stringstream ss;
        ss << "{";
        for (auto s : schedules) ss << s.str() << ", ";
        ss << "}";

        return ss.str();
    }
};
class MinPlatformRequired
{
public:
    static void test()
    {
        MinPlatformRequired obj;
        vector<vector<pair<int, int>>> v = {
            {{900,910}, {940,1200},{950,1120},{1100,1130},{1500,1900},{1800,2000}}
        };

        vector<StationTimeChart> charts;
        for (auto i : v) {
            charts.push_back(StationTimeChart(i));
        }

        for (auto chart : charts) {
            cout << "Processing: {" << chart.str() << "} :";
            auto res = obj.minPlatforms1(chart);
            cout << "Result = " << res << endl;
        }
    }

    int minPlatforms(StationTimeChart chart)
    {
        int result = 0;
        multimap<int, char> map;
        for (auto v : chart.schedules) {
            map.insert({ v.arrival, 'a' });
            map.insert({ v.departure, 'd' });
        }

        int tmp = 0;
        for (auto m : map) {
            if (m.second == 'a') {
                tmp++; if (tmp > result) result = tmp;
            }
            else tmp--;
        }

        return result;
    }

    int minPlatforms1(StationTimeChart chart)
    {
        int result = 0;
        sort(chart.schedules.begin(), chart.schedules.end(), [](const auto& f, const auto& s) {return f.departure < s.departure; });
        int prevEnd = chart.schedules[0].departure;
        int cnt = 1;
        for (auto i = 1; i < chart.schedules.size(); i++) {
            if (chart.schedules[i].arrival <= prevEnd) cnt++;
            else {
                result = max(result, cnt);
                if (cnt > 1) cnt--;
            }
            prevEnd = max(prevEnd, chart.schedules[i].departure);
        }

        return result;
    }

    /*
    *
    *
    Given an array of meetings, find out the minimum number of conference rooms required.

    class Meeting
    {
        long startTime;
        long endTime;
    };

    Got 20 minutes to think through and write the code. Too short in my opinion, but well, it seemed like the interviewer didn't understand C++ either :-).
    struct Meeting {
        int start;
        int end;
        Meeting(int s, int e) {start=s; end=e;}
    };

    bool mysortfunc(Meeting a, Meeting b) { return a.end<b.end; }

    int compute_min_confrooms(vector<Meeting>& meetings)
    {
        // sort meetings w.r.t. their end times
        sort(meetings.begin(),meetings.end(),mysortfunc);

        int peak = 0;
        queue<Meeting> Q;
        Q.push(meetings[0]);
        for(int i=1; i<meetings.size(); i++) {
            while(!Q.empty() && Q.front().end < meetings[i].start) { Q.pop(); }
            Q.push(meetings[i]);
            peak = max(peak, (int)Q.size());
        }

        return peak;
    }

    */
};