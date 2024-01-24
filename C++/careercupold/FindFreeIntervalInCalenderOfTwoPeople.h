#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5739192933941248

Given a set of busy time intervals of two people as in a calendar, find the free time intervals of both the people so as to arrange a new meeting
input: increasing sequence of pair of numbers
per1: (1,5) (10, 14) (19,20) (27,30)
per2: (3,5) (12,15) (18, 21) (23, 24)
ouput: (6,9) (16,17) (22,22) (25,26)


@Phoenix: your output comes from a wrong algorithm, isn't it?

UPDATED:
O(N+M) time algorithm:
- Merge two sorted interval lists into one sorted list, sorted by start time
- Consider the begin of each interval as a time-point;
- For each time-point, keep track of the latest time of any busy period we see so far.
- If this latest time is still before the next time-point, that will be the free period.

Code is quite short:


#include <iostream>
#include <algorithm>
using namespace std;
int N=5;
pair<int,int> Person1[] = { {1,5}, {10, 14}, {19,20}, {21,24}, {27,30} };
int M=4;
pair<int,int> Person2[] = { {3,5}, {12, 15}, {18,21}, {23,24} };

pair<int,int> TimePoints[100];
int C=N+M;

int main()
{
	//merge two sorted lists into a list sorted by start time
	int p1=0, p2=0, k=0;
	while(k<C){
		if (Person1[p1].first <  Person2[p2].first
			||( Person1[p1].first == Person2[p2].first &&
				Person1[p1].second < Person2[p2].second ))
			TimePoints[k++] = Person1[p1++];
		else
			TimePoints[k++] = Person2[p2++];

		if (p1 >=N) while(p2<M) TimePoints[k++] = Person2[p2++];
		if (p2 >=M) while(p1<N) TimePoints[k++] = Person1[p1++];
	};

	//mark latest time so far and print free period
	int latestSoFar = 0;
	for(int i = 0; i < C-1; i++){
		latestSoFar = max(latestSoFar, TimePoints[i].second);
		if (TimePoints[i+1].first > latestSoFar) // next start time is after the latest
			cout <<latestSoFar<<" "<<TimePoints[i+1].first<<endl;
	}
	return 0;
}
*/
class FindFreeIntervalInCalenderOfTwoPeople
{
public:
	static void test() {
		FindFreeIntervalInCalenderOfTwoPeople obj;

		vector<Interval> per1 = { {1, 5}, {10, 14}, {19, 20}, {27, 30} };
		vector<Interval> per2 = { {3, 5}, {12, 15}, {18, 21}, {23, 24} };

		vector<Interval> res = obj.findFreeIntervals1(per1, per2);

		cout << to_string(res) << endl;

		res = obj.findFreeIntervals2(per1, per2);

		cout << to_string(res) << endl;

		res = obj.findFreeIntervals3(per1, per2);

		cout << to_string(res) << endl;
	}

	// start after first interval
	vector<Interval> findFreeIntervals1(vector<Interval>& per1, vector<Interval>& per2)
	{
		vector<Interval> mergedSet = mergeSorted(per1, per2);
		vector<Interval> result;

		int prevEndTime = 0;
		for (int i = 0; i < mergedSet.size() - 1; i++) {
			prevEndTime = max(prevEndTime, mergedSet[i].end);

			if (mergedSet[i + 1].start > prevEndTime) {
				result.push_back({ prevEndTime + 1, mergedSet[i + 1].start - 1 });
			}
		}

		return result;
	}

	// start from rangeStart - 1, rangeEnd - 30
	vector<Interval> findFreeIntervals2(vector<Interval>& per1, vector<Interval>& per2)
	{
		vector<Interval> mergedSet = mergeSorted(per1, per2);
		vector<Interval> result;

		int rangeStart = 1, rangeEnd = 30;
		for (int i = 0; i < mergedSet.size() - 1; i++) {
			if (mergedSet[i].start > rangeStart) {
				result.push_back({ rangeStart + 1, mergedSet[i].start - 1 });
			}

			rangeStart = max(rangeStart, mergedSet[i].end);
		}
		if (rangeStart < rangeEnd) {
			result.push_back({ rangeStart + 1, rangeEnd });
		}

		return result;
	}

	vector<Interval> findFreeIntervals3(vector<Interval>& per1, vector<Interval>& per2)
	{
		int rangeStart = 1, rangeEnd = 30;
		vector<bool> availabilitySet(rangeEnd + 1, true);

		for (auto& it : per1) {
			for (int j = it.start; j <= it.end; j++) {
				availabilitySet[j] = false;
			}
		}

		for (auto& it : per2) {
			for (int j = it.start; j <= it.end; j++) {
				availabilitySet[j] = false;
			}
		}

		int start = -1, end = -1;
		vector<Interval> result;
		for (int i = rangeStart; i <= rangeEnd; i++) {
			if (availabilitySet[i]) {
				if (start == -1) start = i;

				end = i;
			}
			else {
				if (start != -1) {
					result.push_back({ start, end });
				}

				start = end = -1;
			}
		}

		return result;
	}

	vector<Interval> mergeSorted(vector<Interval>& per1, vector<Interval>& per2)
	{
		vector<Interval> result;
		int i = 0, j = 0;
		while (i < per1.size() || j < per2.size()) {
			if (i < per1.size() && j < per2.size()) {
				if (per1[i].start < per2[j].start) {
					result.push_back(per1[i++]);
				}
				else if (per2[i].start < per1[j].start) {
					result.push_back(per2[j++]);
				}
				else if (per1[i].end <= per2[j].end) {
					result.push_back(per1[i++]);
				}
				else {
					result.push_back(per2[j++]);
				}
			}
			else if (i < per1.size()) {
				result.push_back(per1[i++]);
			}
			else {
				result.push_back(per2[j++]);
			}
		}

		return result;
	}
};