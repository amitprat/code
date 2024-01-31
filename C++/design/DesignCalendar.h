#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=15555745
I was asked to design a meeting scheduler, just like in the Microsoft outlook calendar or the gmail calendar.
I proposed that I will create an array of 48 for each day. Every 30 min representing the array entry.
I have to make sure that the next appointment does not collide with a previous meeting.

create a bst, with meeting as the node..
if the root of the meeting is null, and you have one meeting, create a root = new meeting()

make pointer ptr = root;
now, if you have a list of meetings,

for each meeting mi, there is a arrival time a_i, and departure d_i
    if( a_i is between ptr.arrival_time and ptr.departure time)
    return

    if( a_i> ptr.departure_time) ptr=ptr-> right;

    if(d_i< ptr.arrival_time) ptr= ptr->left;
}// loop through all the meetings..
*/

class Calendar
{
    unordered_map<int, bitset<116>> month;
    unordered_map<string, string> meetingDetail;

public:
    bool schedule(int date, pair<int, int> start, pair<int, int> end, string detail)
    {
        int idx1 = get(start);
        int idx2 = get(end);
        auto &bitset = month[date];

        int i = idx1;
        for (; i <= idx2; i++)
            if (bitset.test(i))
                break;
        if (i != idx2 + 1)
        {
            while (meetingDetail.find(key(date, i)) == meetingDetail.end())
                i--;
            cout << "Conflicted with meeting " << meetingDetail[key(date, i)] << " ,exiting.." << endl;
            return false;
        }

        for (i = idx1; i <= idx2; i++)
            bitset.set(i);
        meetingDetail[key(date, idx1)] = detail;

        cout << "Meeting " << meetingDetail[key(date, idx1)] << " scheduled successfully" << endl;
        return true;
    }

    pair<bool, string> hasConflict(int date, pair<int, int> start, pair<int, int> end)
    {
        int idx1 = get(start);
        int idx2 = get(end);
        auto &bitset = month[date];

        int i = idx1;
        for (; i <= idx2; i++)
            if (bitset.test(i))
                break;
        if (i == idx2 + 1)
            return {false, ""};

        return {true, meetingDetail[key(date, i)]};
    }

    string key(int date, int start)
    {
        return "{" + to_string(date) + "," + std::to_string(start) + "}";
    }

    int get(pair<int, int> start)
    {
        return 4 * start.first + (start.second / 15);
    }

    public:
    static void test()
{
    Calendar calendar;
    auto res = calendar.schedule(03, {9, 30}, {10, 30}, "Meeting1");
    cout << res << endl;
    res = calendar.schedule(03, {10, 00}, {10, 30}, "Meeting2");
    cout << res << endl;
    return 0;
}
};
