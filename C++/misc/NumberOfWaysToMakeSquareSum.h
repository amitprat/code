#pragma once
#include "../header.h"

/*
Input:  n = 100
Output: 1
100 can be written as 10^2. Note that 100 can also be  written as 5^2 + 5^2 + 5^2 + 5^2, but this
representation requires 4 squares.

Input:  n = 6
Output: 3
*/

class NumberOfWaysToMakeSquareSum {
   public:
    static void test() {
        NumberOfWaysToMakeSquareSum obj;
        for (int i = 0; i < 100; i++) {
            int minWays1 = obj.minWaysToMakeSquareSumDP(i);
            int minWays2 = obj.minWaysToMakeSquareSumRecursive(i);

            int numWays1 = obj.numWaysToMakeSquareSumDP(i);
            int numWays2 = obj.numWaysToMakeSquareSumRecursive(i);

            cout << format("Min ways to make square sum of {0} are {1}, {2}", i, minWays1, minWays2) << endl;
            cout << format("Total ways to make square sum of {0} are {1}, {2}", i, numWays1, numWays2) << endl;

            assert(minWays1 == minWays2);
            assert(numWays1 == numWays2);
        }
    }

   public:
    int minWaysToMakeSquareSumRecursive(int n) {
        if (n <= 1) return n;

        int mn = INT_MAX;
        for (int i = 1; i * i <= n; i++) {
            mn = min(mn, 1 + minWaysToMakeSquareSumRecursive(n - i * i));
        }

        return mn;
    }

    int numWaysToMakeSquareSumRecursive(int n) {
        if (n < 0) return 0;
        if (n == 0) return 1;

        int ways = 0;
        for (int i = 1; i * i <= n; i++) {
            ways += numWaysToMakeSquareSumRecursive(n - i * i);
        }

        return ways;
    }

   public:
    int minWaysToMakeSquareSumDP(int n) {
        int dp[n + 1];
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;

        for (int i = 4; i <= n; i++) {
            dp[i] = i;
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], 1 + dp[i - j * j]);
            }
        }

        return dp[n];
    }

    int numWaysToMakeSquareSumDP(int n) {
        vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i * i <= n; i++) {
            dp[i] = 0;
            for (int j = 1; j <= n; j++) {
                dp[j] += dp[j - i * i];
            }
        }

        return dp[n];
    }
};