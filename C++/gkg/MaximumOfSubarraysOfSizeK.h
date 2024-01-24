#pragma once
#include "../Header.h"

class MaximumOfSubarraysOfSizeK {
public:
    static void test() {
        MaximumOfSubarraysOfSizeK obj;
        int N = 9, K = 3;
        int arr[] = { 1, 2, 3, 1, 4, 5, 2, 3, 6 };

        auto res = obj.max_of_subarrays(arr, N, K);
        cout << to_string(res) << endl;
    }

    vector <int> max_of_subarrays(int* arr, int n, int k)
    {
        deque<int> dq;
        vector<int> result;
        for (int i = 0; i < n; i++) {
            while (!dq.empty() && arr[i] >= arr[dq.back()]) dq.pop_back();
            while (!dq.empty() && dq.front() + k <= i) dq.pop_front();
            dq.push_back(i);

            if (i >= k - 1) {
                result.push_back(arr[dq.front()]);
            }
        }

        while (!dq.empty()) {
            cout << dq.front() << " ";
            dq.pop_front();
        }
        cout << endl;

        return result;
    }
};