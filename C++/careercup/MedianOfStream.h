#pragma once
#include "../header.h"

class MedianOfStream {
    // [1,2,3,9,4,5,6]
    // <------max heap-----> | <------min heap------>
    // ------------------inserting 1-----------------
    // 1---------------------| ----------------------
    // ----------------------| 1---------------------
    // 1---------------------| ----------------------
    // ------------------inserting 2-----------------
    // 2 1 ------------------| ----------------------
    // 1 --------------------| 2 --------------------
    // ------------------inserting 3-----------------
    // 3 1 ------------------| 2 --------------------
    // 1 --------------------| 2 3 ------------------
    // ------------------inserting 9-----------------
    // 9 1 ------------------| 2 3 ------------------
    // 1 --------------------| 2 3 9-----------------
    // 2 1-------------------| 3 9-------------------
    // ------------------inserting 4-----------------
    // 4 2 1 ----------------| 3 9 ------------------
    // 2 1 ------------------| 3 4 9 ----------------
    // so on
    //
    // insert item to max heap first (left side)
    // take the largest item on left and put it on right side (right side)
    // if left side < right side :
    //     take smallest element from right side and put on left side
    // At the end of it:
    //    left side is always larger than right side.
    //    elements on left and right side are sorted. (left half is reverse sorted)
    // If left is greater : take that from left side.
    // if both are of same size, then array is of equal size and take median of those.
    //
   private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

   public:
    static void test() {
        MedianOfStream obj;
        vector<int> res;
        vector<int> nums = {7, 1, 4, 2, 4, 3, 8, 9, 2, 4, 1, 5, 10, 6};
        for (auto& num : nums) {
            println("Items so far: {}", res);
            println("Median so far: {}", obj.get());
            println();

            res.push_back(num);
            obj.add(num);
        }
    }

   public:
    void add(int val) {
        maxHeap.push(val);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double get() {
        if (maxHeap.empty()) return -1;
        if (maxHeap.size() > minHeap.size()) return maxHeap.top();
        return (minHeap.top() + maxHeap.top()) / 2.0;
    }
};