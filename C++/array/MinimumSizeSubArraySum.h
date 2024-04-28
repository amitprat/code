#pragma once
#include "../header.h"

class MinimumSizeSubArraySum {
   public:
    static void test() {
        MinimumSizeSubArraySum obj;

        vector<pair<vector<int>, int>> tests = {
            {{2, 3, 1, 2, 4, 3}, -10},
            {{2, 3, 1, 2, 4, 3}, -1},
            {{2, 3, 1, 2, 4, 3}, 0},
            {{2, 3, 1, 2, 4, 3}, 1},
            {{2, 3, 1, 2, 4, 3}, 2},
            {{2, 3, 1, 2, 4, 3}, 3},
            {{2, 3, 1, 2, 4, 3}, 4},
            {{2, 3, 1, 2, 4, 3}, 5},
            {{2, 3, 1, 2, 4, 3}, 6},
            {{2, 3, 1, 2, 4, 3}, 7},
            {{2, 3, 1, 2, 4, 3}, 8},
            {{2, 3, 1, 2, 4, 3}, 9},
            {{2, 3, 1, 2, 4, 3}, 10},
            {{2, 3, 1, 2, 4, 3}, 45}};

        for (auto& test : tests) {
            auto res = obj.getMinimumSizeSubArray(test.first, test.second);
            cout << "MinLengthSubarray for sum:" << setw(3) << test.second
                 << " :: (" << res.second.first << "," << res.second.second << ") = " << res.first << endl;

            auto res1 = obj.smallestSubarraySum(test.first, test.second);
            cout << "Minimum length subarray: " << res1 << endl;

            auto res2 = obj.findMinLen(test.first, test.second);
            cout << "Minimum length subarray: " << res2 << endl;
        }
    }

    pair<int, pair<int, int>> getMinimumSizeSubArray(vector<int>& a, int s) {
        int l = 0, r = 0;
        pair<int, pair<int, int>> result = {0, {-1, -1}};
        int curSum = 0;

        while (r < a.size()) {
            if (curSum < s) {
                curSum += a[r++];
            } else if (l < r) {
                if (result.second.first == -1 || r - l < result.second.second - result.second.first)
                    result = {curSum, {l, r - 1}};

                curSum -= a[l++];
            } else {
                l++;
                r++;
            }
        }

        return result;
    }

   private:
    int smallestSubarraySum(vector<int>& arr, int sum) {
        int curSum = 0;
        int mnLen = arr.size() + 1;

        int start = 0, end = 0;
        while (end < arr.size()) {
            while (curSum < sum && end < arr.size()) {
                curSum += arr[end++];
            }

            while (curSum > sum && start <= end) {
                if (end - start < mnLen) {
                    mnLen = end - start;
                }

                curSum -= arr[start++];
            }

            end++;
        }

        return mnLen;
    }

   private:
    vector<int> findMinLen(vector<int> arr, int sum) {
        int l = 0, r = 0, curSum = 0;
        pair<int, int> window = {-1, -1};

        while (r < arr.size()) {
            curSum += arr[r];

            while (l <= r && curSum - arr[l] > sum) {
                if (window.first == -1 || r - l < window.second - window.first) {
                    window = {l, r};
                }

                curSum -= arr[l++];
            }

            r++;
        }

        vector<int> response;
        if (window.first != -1) {
            for (int i = window.first; i <= window.second; i++) response.push_back(arr[i]);
        }

        return response;
    }
};