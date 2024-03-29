#include "../header.h"

/*
https://www.careercup.com/question?id=19286669

Given life time of different animals. Find period when maximum number of animals lived. ex [5, 11], [6, 18], [2, 5],[3,12] etc.
year in which max no animals exists.
Input intervals (or lifetimes): [5, 11], [6, 18], [2, 5], [3,12]

1. Put the end and start times of the intervals in one array. Sort it!. Always put the start time before end time in case they are equal.
Maintain flags to identify a start/end interval. For above input I'll do something like: [2S, 3S, 5S, 5E, 6S, 11E, 12E, 18E]

2. Now scan the array from left to right keeping track of how many intervals we are in.
(This would be equal to total numbers of start intervals - total number of end intervals encountered so far).
For above input I'll get something like: [1, 2, 3, 2, 3, 2, 1, 0]

3. Now pick the maxima points from step 2. All the maxima points will be Start intervals and the point next to a maxima point will
always be an end interval (which will be the end of the maxima start interval). So we'll get: [5S,5E] and [6S,11E].

Hence the result is [5,5], [6,11]

Time complexity = O(nLogn), because of sorting in step 1.
Space complexity = O(n)
*/
class MaximumAnimalLivedPeriod {
   public:
    static void test() {
        MaximumAnimalLivedPeriod obj;
        vector<Interval> intervals = {{5, 11}, {6, 18}, {2, 5}, {3, 12}};

        {
            auto res = obj.findMaxPeriod1(intervals);
            cout << "Max Period (Approach1) = " << res.first << ":" << res.second.to_string() << endl;

            auto res2 = obj.findMaxPeriod2(intervals);
            cout << "Max Period (Approach2) = " << res2.first << ", " << res2.second << endl;

            auto res3 = obj.findMaxPeriod3(intervals);
            cout << "Max Period (Approach3) = " << res3.first << ", " << res3.second << endl;
        }
    }

   private:
    // Approach1: construct start end end intervals in a array as  [10S, 11S, 15E, 20E,..]
    // Then sort the array in increasing order keeping start interval first if both are same.
    // Then iterate over the array and count the max number of starts by incrementing on 'S' and decreasing on 'E'.
    // The max interval is the [max(Starts), min(End)]
    pair<int, Interval> findMaxPeriod1(vector<Interval> intervals) {
        multimap<int, char> m;
        int period = 0;
        Interval curPeriod = {INT_MIN, INT_MAX};
        int mxPeriodCount = 0;
        Interval maxPeriod = curPeriod;

        for (auto interval : intervals) {
            m.insert({interval.start, 'a'});
            m.insert({interval.end, 'd'});
        }

        for (auto entry : m) {
            if (entry.second == 'a') {
                curPeriod.start = max(curPeriod.start, entry.first);
                period++;
            } else if (entry.second == 'd') {
                curPeriod.end = entry.first;
                if (period > mxPeriodCount) {
                    maxPeriod = curPeriod;
                    mxPeriodCount = period;
                }
                period--;
            }
        }
        mxPeriodCount = max(mxPeriodCount, period);

        return {mxPeriodCount, maxPeriod};
    }

   private:
    // Similar to above approach but keeping them seperate arrays to sort.
    pair<int, vector<Interval>> findMaxPeriod2(vector<Interval>& in) {
        int n = in.size();
        vector<int> s(n);
        vector<int> e(n);

        for (int i = 0; i < n; i++) {
            s[i] = in[i].start;
            e[i] = in[i].end;
        }
        sort(s.begin(), s.end());
        sort(e.begin(), e.end());

        vector<Interval> results;
        int maxDiff = 0;

        int i = 0, j = 0;
        while (i < n && j < n) {
            if (s[i + 1] <= e[j]) {
                i++;
            } else {
                if (i - j + 1 > maxDiff) {
                    maxDiff = i - j + 1;
                    results.clear();
                    results.push_back(Interval(s[i], e[j]));
                } else if (i - j + 1 >= maxDiff) {
                    results.push_back(Interval(s[i], e[j]));
                }

                j++;
            }
        }

        return {maxDiff, results};
    }

   private:
    /*
    Solution 2 -
    Explanation -

    but i think this will also work
    1.Firstly take an array arr[100],initialize it to zero.
    2.for every interval do +1 for eg, [5, 7] ,do arr[5]++,arr[6]++.arr[7]++;
    3.now traverse again and you got all intervals for max value.
    i think in this case time complexity is O(n).
    */
    pair<int, vector<Interval>> findMaxPeriod3(vector<Interval>& intervals) {
        int range = 100;  // consider max age range is 100
        vector<int> lifetime(range, 0);

        for (auto& it : intervals) {
            for (int i = it.start; i <= it.end; i++) lifetime[i]++;
        }

        int maxAnimals = 0;
        for (int i = 0; i < range; i++) {
            maxAnimals = max(maxAnimals, lifetime[i]);
        }

        vector<Interval> result;
        for (int i = 0; i < range - 1; i++) {
            if (lifetime[i] == maxAnimals) {
                int j = i;
                while (j < range && lifetime[j] == lifetime[i]) j++;
                result.push_back({i, j - 1});
            }
        }

        return {maxAnimals, result};
    }

   private:
    /*
    Solution 3 -
    Explanation -
    Time = O(nlogn)
    Space = O(n)

    1) Sort all intervals according to start time.
    2) Select the ith[i ->1,n] interval and merge to all previous intervals and keep on counting.
    Example -
    (2,5), (3,12) , (5,11) , (6,18) - [1,1,1,1]
    (3,5), (3,12) , (5,11) , (6,18) - [2,1,1,1]
    (5,5), (5,11) , (5,11) , (6,18) - [3,2,1,1]
    (5,5), (6,11) , (6,11) , (6,18) - [3,3,2,1]

    Pick up all the max intervals (5,5) and (6,11);
    */
};