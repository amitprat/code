#pragma once
#include "../Header.h"
using namespace std;

/*
https://www.careercup.com/question?id=14680789

There is a bus stand. We have given arrival time of the buses and halt of every bus. timings can overlap. We have to find minimum no of platform on the bus stand, so that no bus has to wait to occupy platform.

sort the timings (both arrival and departure )

intilaize two variables count and max equal to 0

whenever there is an arrival increment count and and when there is a departure decrement count

and at every step (increment or decrement ) compare it with max and then if count is greater than max update it .....

return max

max is nothing but the maximum no of buses going to be there at any point of time
so there need to max number of platforms
*/

class MinPlatformRequired
{
    class StationTimeChart
    {
    public:
        class Schedule
        {
        public:
            int arrival;
            int departure;
            Schedule(int arrival, int departure) : arrival(arrival), departure(departure) {}
            string to_string() {
                return "{" + std::to_string(arrival) + ", " + std::to_string(departure) + "}";
            }
        };

        vector<Schedule> schedules;

    public:
        StationTimeChart(vector<pair<int, int>>& schedules) {
            for (auto& s : schedules) {
                this->schedules.push_back(Schedule(s.first, s.second));
            }
        }
        string str() {
            stringstream ss;
            ss << "[";
            for (auto& i : schedules) ss << i.to_string() << ", ";
            if (ss.str().size() > 2) { ss.seekp(-2, std::ios_base::end); }
            ss << "]";
            return ss.str();
        }
    };

public:
    static void test()
    {
        MinPlatformRequired obj;
        vector<vector<pair<int, int>>> trainSchedules = {
            {{900,910}, {940,1200},{950,1120},{1100,1130},{1500,1900},{1800,2000}},
            {{1000,1800},{1100, 1700}, {1200,1230},{1300,1400},{1330,1430},{1400,1500},{1600,1700},{1630,1800}}
        };

        vector<StationTimeChart> charts;
        for (auto& trainSchedule : trainSchedules) {
            charts.push_back(StationTimeChart(trainSchedule));
        }

        for (auto& chart : charts) {
            cout << "Processing: {" << chart.str() << "} :";

            auto res0 = obj.minPlatforms0(chart);
            auto res1 = obj.minPlatforms1(chart);
            auto res2 = obj.minPlatforms2(chart);
            auto res3 = obj.minPlatforms3(chart);
            auto res4 = obj.minPlatforms4(chart);
            auto res5 = obj.minPlatforms5(chart);

            assert(res1 == res0);
            assert(res1 == res2);
            assert(res1 == res3);
            assert(res1 == res4);
            assert(res1 == res5);

            cout << "Result = " << res1 << endl;
        }
    }

    // Maintain seperate queue for each of the bus and look for best queue where we can fit next bus
    // Bad time and space complexity
    int minPlatforms0(StationTimeChart& chart)
    {
        int result = 0;
        if (chart.schedules.empty()) return result;

        vector<queue<StationTimeChart::Schedule>> vq;
        vector<StationTimeChart::Schedule> schedules = chart.schedules;
        sort(schedules.begin(), schedules.end(), [](auto& f, auto& s) {return f.arrival < s.arrival; });

        queue<StationTimeChart::Schedule> q; q.push(schedules[0]);
        vq.push_back(q);

        for (int i = 1; i < schedules.size(); i++) {
            bool found = false;
            for (auto& q : vq) {
                if (schedules[i].arrival > q.back().departure) {
                    q.push(schedules[i]);
                    found = true;
                    break;
                }
            }

            if (!found) {
                queue<StationTimeChart::Schedule> tmp; tmp.push(schedules[i]);
                vq.push_back(tmp);
            }
        }

        return vq.size();
    }

    /*
    Time Complexity: O( N* LogN).
    Since we are inserting into multiset and it maintain elements in sorted order. So N insert operations in multiset requires N*LogN time complexity.
    */
    int minPlatforms1(StationTimeChart& chart)
    {
        int result = 0;
        // multimap won't work here if arrival and departure time are same.
        // https://stackoverflow.com/questions/52074218/custom-compare-function-for-stdmultimap-when-keys-are-equal
        // multisort will instead first sort by first value in pair and then second. because 'a' < 'd' so it will maintain order

        multiset<pair<int, char>> multiset;
        for (auto& schedule : chart.schedules) {
            multiset.insert({ schedule.arrival, 'a' });
            multiset.insert({ schedule.departure, 'd' });
        }

        int platCnt = 0;
        for (auto& e : multiset) {
            if (e.second == 'a') {
                platCnt++;
                result = max(result, platCnt);
            }
            else platCnt--;
        }

        return result;
    }

    // T - O(nlogn)
    int minPlatforms2(StationTimeChart& chart)
    {
        int n = chart.schedules.size();
        if (n == 0) return 0;

        vector<int> startTimes, endTimes;
        for (auto& e : chart.schedules) {
            startTimes.push_back(e.arrival);
            endTimes.push_back(e.departure);
        }
        sort(startTimes.begin(), startTimes.end());
        sort(endTimes.begin(), endTimes.end());

        int a = 1, d = 0;
        int result = 1;
        while (a < n) {
            if (endTimes[d] < startTimes[a]) d++;
            else a++;

            result = max(result, a - d);
        }

        return result;
    }

    /*
    Complexity Analysis:

    Time Complexity: O(N).
    Space Complexity: O(1).
    */
    int minPlatforms3(StationTimeChart& chart)
    {
        int platform[2361] = { 0 };
        int requiredPlatform = 1;

        for (int i = 0; i < chart.schedules.size(); i++) {
            // increment the platforms for arrival
            ++platform[chart.schedules[i].arrival];

            // once train departs we decrease the platform count
            --platform[chart.schedules[i].departure + 1];
        }

        // We are running loop till 2361 because maximum time value in a day can be 23:60
        for (int i = 1; i < 2361; i++) {
            // taking cumulative sum of platform give us required
            // number of platform for every minute
            platform[i] = platform[i] + platform[i - 1];
            requiredPlatform = max(requiredPlatform, platform[i]);
        }

        return requiredPlatform;
    }

    // https://www.programcreek.com/2014/05/leetcode-meeting-rooms-ii-java/
    int minPlatforms4(StationTimeChart& chart) {
        vector<StationTimeChart::Schedule> schedules = chart.schedules;
        if (schedules.empty()) return 0;

        sort(schedules.begin(), schedules.end(), [](auto& f, auto& s) {return f.arrival < s.arrival; });

        priority_queue<int, vector<int>, greater<int>> minheap;
        int count = 0;

        for (StationTimeChart::Schedule& schedule : schedules) {
            if (minheap.empty()) {
                count++;
                minheap.push(schedule.departure);
            }
            else {
                if (schedule.arrival <= minheap.top()) {
                    count++;
                }
                else {
                    minheap.pop();
                }

                minheap.push(schedule.departure);
            }
        }

        return count;
    }

    // https://www.careercup.com/question?id=5142448749674496
    int minPlatforms5(StationTimeChart& chart)
    {
        int minPlatformReq = 0;
        if (chart.schedules.empty()) return minPlatformReq;

        vector<StationTimeChart::Schedule> schedules = chart.schedules;
        sort(schedules.begin(), schedules.end(), [](const auto& f, const auto& s) {
            if (f.departure != s.departure) return f.departure < s.departure;
            return f.arrival < s.arrival;
            });

        queue<StationTimeChart::Schedule> q;
        q.push(schedules[0]);

        for (auto i = 1; i < schedules.size(); i++) {
            while (!q.empty() && q.front().departure < schedules[i].arrival) { q.pop(); }

            q.push(schedules[i]);
            minPlatformReq = max(minPlatformReq, (int)q.size());
        }

        return minPlatformReq;
    }

    // This won't work
    //int minPlatforms6(StationTimeChart& chart)
    //{
    //    int minPlatformReq = 0;
    //    if (chart.schedules.empty()) return minPlatformReq;

    //    sort(chart.schedules.begin(), chart.schedules.end(), [](const auto& f, const auto& s) {return f.departure < s.departure; });

    //    int prevEnd = chart.schedules[0].departure;
    //    int platformCnt = 1;
    //    for (auto i = 1; i < chart.schedules.size(); i++) {
    //        if (chart.schedules[i].arrival <= prevEnd) platformCnt++;
    //        else {
    //            minPlatformReq = max(minPlatformReq, platformCnt);
    //            if (platformCnt > 1) platformCnt--;
    //        }
    //        prevEnd = max(prevEnd, chart.schedules[i].departure);
    //    }
    //    minPlatformReq = max(minPlatformReq, platformCnt);

    //    return minPlatformReq;
    //}

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

    bool mysortfunc(Meeting a, Meeting b) { return a.end < b.end; }

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