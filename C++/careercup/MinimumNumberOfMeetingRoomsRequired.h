#include "../header.h"

class MinimumNumberOfMeetingRoomsRequired {
    struct Interval {
        int start, end;
        string to_string() {
            stringstream ss;
            ss << "{";
            ss << start << "," << end;
            ss << "}";

            return ss.str();
        }
    };

   public:
    static void test() {
        MinimumNumberOfMeetingRoomsRequired obj;
        vector<Interval> meetings = {
            {0, 30},
            {5, 10},
            {15, 20},
            {25, 40},
            {35, 50}};

        cout << format("Min meeting rooms={}", obj.minNumberOfMeetingRooms1(meetings)) << endl;
        obj.minNumberOfMeetingRooms2(meetings);

        cout << format("Min meeting rooms={}", obj.minNumberOfMeetingRooms3(meetings)) << endl;
    }

   private:
    int minNumberOfMeetingRooms1(vector<Interval>& meetings) {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        sort(meetings.begin(), meetings.end(), [](auto& f, auto& s) { return f.start < s.start; });

        for (auto& meeting : meetings) {
            if (!minHeap.empty() && meeting.start >= minHeap.top()) {
                minHeap.pop();
            }
            minHeap.push(meeting.end);
        }

        return minHeap.size();
    }

   private:
    void minNumberOfMeetingRooms2(vector<Interval>& meetings) {
        auto comparator = [](const auto& f, const auto& s) { return f.end < s.end; };
        list<priority_queue<Interval, vector<Interval>, decltype(comparator)>> minHeaps;
        sort(meetings.begin(), meetings.end(), [](auto& f, auto& s) { return f.start < s.start; });

        for (auto& meeting : meetings) {
            bool found = false;
            for (auto& q : minHeaps) {
                if (!q.empty() && meeting.start >= q.top().end) {
                    q.push(meeting);
                    found = true;
                    break;
                }
            }

            if (!found) {
                minHeaps.push_back({});
                minHeaps.back().push(meeting);
            }
        }

        for (auto& q : minHeaps) {
            while (!q.empty()) {
                auto interval = q.top();
                cout << interval.to_string() << " ";
                q.pop();
            }
            cout << endl;
        }

        cout << format("Minimum number of meeting rooms required={}", minHeaps.size()) << endl;
    }

   private:
    int minNumberOfMeetingRooms3(vector<Interval>& meetings) {
        vector<pair<int, char>> vals;

        for (auto& meeting : meetings) {
            vals.push_back({meeting.start, 'f'});
            vals.push_back({meeting.end, 's'});
        }

        sort(vals.begin(), vals.end(), [](const auto& f, const auto& s) {
            if (f.first < s.first) return true;
            if (f.first > s.first) return false;
            return f.second < s.second;
        });

        int minRooms = 0;
        int cur = 0;
        for (auto& val : vals) {
            if (val.second == 'f')
                cur++;
            else {
                minRooms = max(minRooms, cur);
                cur--;
            }
        }

        return minRooms;
    }
};