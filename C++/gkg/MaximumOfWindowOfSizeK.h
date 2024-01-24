#pragma once
#include "../Header.h"

class MaximumOfWindowOfSizeK {
public:
    static void test() {
        vector<int> arr = { 12, 1, 78, 90, 57, 89, 56 };
        int k = 3;

        deque<int> dq;

        vector<int> res;
        for (int i = 0; i < arr.size(); i++) {
            while (!dq.empty() && arr[dq.back()] < arr[i]) dq.pop_back();
            while (!dq.empty() && i - dq.front() >= k) dq.pop_front();

            dq.push_back(i);
            if (i >= k - 1) {
                res.push_back(arr[i]);
            }
        }

        cout << to_string(res) << endl;
    }
};