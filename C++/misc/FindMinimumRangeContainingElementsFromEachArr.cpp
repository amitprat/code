#pragma once
#include "../ds/PriorityQueue.h"
#include "../header.h"

/*
http://www.careercup.com/question?id=16759664
You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists.

For example,
List 1: [4, 10, 15, 24, 26]
List 2: [0, 9, 12, 20]
List 3: [5, 18, 22, 30]

The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.
*/

class FindMinimumRangeContainingElementsFromEachArr {
    using Pair = pair<int, int>;

    struct Element {
        int element;
        int arrPos;
        int arrIdx;
    };

   private:
    Pair minrange(const vector<vector<int>>& arrs) {
        Pair minRange = {-1, -1};

        int minLen = INT_MAX;
        int curMin = INT_MAX;
        int curMax = INT_MIN;

        PriorityQueue<Element> pq([](const auto& first, const auto& second) { return first.element < second.element; });

        for (int i = 0; i < arrs.size(); i++) {
            auto arr = arrs[i];

            pq.insert(Element(arr[0], i, 0));

            curMin = min(curMin, arr[0]);
            curMax = max(curMax, arr[0]);

            if (curMax - curMin + 1 > minLen) {
                minLen = curMax - curMin + 1;
                minRange = Pair(curMin, curMax);
            }
        }

        while (true) {
            Element mnElem = pq.top();
            pq.pop();

            // if no next element, break;
            if (mnElem.arrIdx + 1 >= arrs[mnElem.arrPos].size()) break;

            curMin = arrs[mnElem.arrPos][mnElem.arrIdx];

            // insert next element.
            pq.insert(Element{arrs[mnElem.arrPos][mnElem.arrIdx + 1], mnElem.arrPos, mnElem.arrIdx + 1});

            // update curMax
            if (arrs[mnElem.arrPos][mnElem.arrIdx + 1] > curMax) curMax = max(curMax, arrs[mnElem.arrPos][mnElem.arrIdx + 1]);

            // consider new possible range
            if (curMax - curMin + 1 > minLen) {
                minLen = curMax - curMin + 1;
                minRange = Pair(curMin, curMax);
            }
        }

        return minRange;
    }

   private:
    Pair minrange1(const vector<vector<int>>& arrs) {
        Pair minRange = {-1, -1};

        int minLen = INT_MAX;
        int curMin = INT_MAX;
        int curMax = INT_MIN;

        PriorityQueue<Element> pq([](const auto& first, const auto& second) { return first.element < second.element; });

        for (int i = 0; i < arrs.size(); i++) {
            auto arr = arrs[i];

            pq.insert(Element(arr[0], i, 0));

            curMin = min(curMin, arr[0]);
            curMax = max(curMax, arr[0]);
        }

        while (true) {
            // consider new possible range
            if (curMax - curMin + 1 > minLen) {
                minLen = curMax - curMin + 1;
                minRange = Pair(curMin, curMax);
            }

            Element mnElem = pq.top();
            pq.pop();

            // if no next element, break;
            if (mnElem.arrIdx + 1 >= arrs[mnElem.arrPos].size()) break;

            curMin = arrs[mnElem.arrPos][mnElem.arrIdx];

            // insert next element.
            pq.insert(Element{arrs[mnElem.arrPos][mnElem.arrIdx + 1], mnElem.arrPos, mnElem.arrIdx + 1});

            // update curMax
            if (arrs[mnElem.arrPos][mnElem.arrIdx + 1] > curMax) curMax = max(curMax, arrs[mnElem.arrPos][mnElem.arrIdx + 1]);
        }

        return minRange;
    }
};