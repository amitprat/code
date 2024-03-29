#include "../header.h"
/*
You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.
Example:

Consider the following 6 activities.
     start[]  =  {1, 3, 0, 5, 8, 5};
     finish[] =  {2, 4, 6, 7, 9, 9};
The maximum set of activities that can be executed
by a single person is {0, 1, 3, 4}
The greedy choice is to always pick the next activity whose finish time is least among the remaining activities and the start time is more than or equal to the finish time of previously selected activity. We can sort the activities according to their finishing time so that we always consider the next activity as minimum finishing time activity.

1) Sort the activities according to their finishing time
2) Select the first activity from the sorted array and print it.
3) Do following for remaining activities in the sorted array.
…….a) If the start time of this activity is greater than the finish time of previously selected activity then select this activity and print it.
*/

class ActivitySelection {
   private:
    int findMax(Interval it[], int n) {
        sort(it, it + n, [](const auto& it1, const auto& it2) { return it1.end < it2.end; });

        vector<Interval> result;
        result.push_back(it[0]);
        itn finish = it[0].finish;
        for (int i = 1; i < n; i++) {
            if (it[i].start >= finish) {
                result.push_back(it[i]);
                finish = it[i].finish;
            }
        }
        for (int i = 0; i < result.size(); i++)
            cout << "( " << result[i].start << "," << result[i].finish << ") ,";
        cout << endl;
        return result.size();
    }
};
