#pragma once
#include "../header.h"

class MaxSumWithNoAdjElements {
   public:
    int findMaxSum(vector<int>& arr, int i, int n) {
        if (i >= n) return 0;

        return max(arr[i] + findMaxSum(arr, i + 2, n), findMaxSum(arr, i + 1, n));
    }

   public:
    int findMaxSumMemo(vector<int>& arr) {
        vector<int> dp(arr.size(), -1);

        return findMaxSumMemo(arr, 0, arr.size(), dp);
    }
    int findMaxSumMemo(vector<int>& arr, int i, int n, vector<int>& dp) {
        if (i >= n) return 0;
        if (dp[i] != -1) return dp[i];

        dp[i] = max(arr[i] + findMaxSum(arr, i + 2, n), findMaxSum(arr, i + 1, n));

        return dp[i];
    }

   public:
    int findMaxSumDP(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;

        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = arr[0];

        for (int i = 1; i < n; i++) {
            dp[i][1] = dp[i - 1][0] + arr[i];
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
        }

        return max(dp[n - 1][0], dp[n - 1][1]);
    }

   public:
    int findMaxSumDP2(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;

        int excl = 0, incl = arr[0];
        for (int i = 1; i < n; i++) {
            auto excl_new = max(excl, incl);
            incl = excl + arr[i];
            excl = excl_new;
        }

        return max(incl, excl);
    }
};