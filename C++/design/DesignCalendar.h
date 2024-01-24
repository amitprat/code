/*
https://www.careercup.com/question?id=15555745

I was asked to design a meeting scheduler, just like in the Microsoft outlook calendar or the gmail calendar. I proposed that I will create an array of 48 for each day. Every 30 min representing the array entry.

I have to make sure that the next appointment does not collide with a previous meeting.

My solution works fine but it wastes too much memory.

Can anyone please tell me how do I find a better solution to detect collision for meetings.

I don't know all the meetings at the beginning. They will be added randomly later.

Thanks,
*/

/*
just exploring this idea:

create a bst, with meeting as the node..
if the root of the meeting is null, and you have one meeting, create a root = new meeting()

make pointer ptr = root;
now, if you have a list of meetings,
for each meeting mi, there is a arrival time a_i,
and departure d_i
if( a_i is between ptr.arrival_time and ptr.departure time)
return

if( a_i> ptr.departure_time) ptr=ptr-> right;

if(d_i< ptr.arrival_time) ptr= ptr->left;
}// loop through all the meetings..

and construct a binary tree..

let me know what you think on this?
*/

package com.test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import static com.test.MeetingScheduler.TimeSlot.createNewSlot;

public
class MeetingScheduler
{

private
    Map<TimeSlot, Meeting> meetings = new HashMap<>();

public
    static void main(String[] args)
    {
        MeetingScheduler scheduler = new MeetingScheduler();
        System.out.println(scheduler.add(new Meeting("First meeting"), createNewSlot("03/01/2013 08:00", "03/01/2013 08:30")));
        System.out.println(scheduler.add(new Meeting("Second meeting"), createNewSlot("03/01/2013 08:30", "03/01/2013 09:30")));

        System.out.println(scheduler.add(new Meeting("Third meeting"), createNewSlot("03/01/2013 07:30", "03/01/2013 08:15")));

        System.out.println(scheduler.add(new Meeting("Fourth meeting"), createNewSlot("03/01/2013 09:15", "03/01/2013 09:45")));

        scheduler.printAllMeetings();
    }

private
    void printAllMeetings()
    {
        System.out.println(meetings);
    }

public
    boolean add(Meeting meeting, TimeSlot timeSlot)
    {
        for (TimeSlot slot : meetings.keySet())
        {
            if (slot.collidesWith(timeSlot))
            {
                return false;
            }
        }
        meetings.put(timeSlot, meeting);
        return true;
    }

public
    static class Meeting
    {
    private
        String title;

    public
        Meeting(String title)
        {
            this.title = title;
        }

    public
        String toString()
        {
            return title;
        }
    }

    public static class TimeSlot
    {
    private
        Date beginDate;
    private
        Date endDate;

    public
        TimeSlot(Date beginDate, Date endDate)
        {
            this.beginDate = beginDate;
            this.endDate = endDate;
        }

    public
        boolean collidesWith(TimeSlot timeSlot)
        {

            if (timeSlot.beginDate.getTime() > beginDate.getTime() && timeSlot.beginDate.getTime() < endDate.getTime())
            {
                return true;
            }

            if (timeSlot.endDate.getTime() > beginDate.getTime() && timeSlot.endDate.getTime() < endDate.getTime())
            {
                return true;
            }
            return false;
        }

    public
        static TimeSlot createNewSlot(String beginDate, String endDate)
        {
            SimpleDateFormat format = new SimpleDateFormat("MM/dd/yyyy hh:mm");
            try
            {
                return new TimeSlot(format.parse(beginDate), format.parse(endDate));
            }
            catch (ParseException e)
            {
                e.printStackTrace();
            }
            return null;
        }

    public
        String toString()
        {
            return "Begin Date = " + beginDate.toString() + ", End Date = " + endDate.toString();
        }
    }
}

// Calendar

#include <bits/stdc++.h>
#include <bitset>
using namespace std;

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
};

int main()
{
    Calendar calendar;
    auto res = calendar.schedule(03, {9, 30}, {10, 30}, "Meeting1");
    cout << res << endl;
    res = calendar.schedule(03, {10, 00}, {10, 30}, "Meeting2");
    cout << res << endl;
    return 0;
}
