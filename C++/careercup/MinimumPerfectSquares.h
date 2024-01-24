#include "../header.h"

/*
https://careercup.com/question?id=5725584103571456

Given a number "n", find the least number of perfect square numbers sum needed to get "n"

Example:
n=12, return 3 (4 + 4 + 4) = (2^2 + 2^2 + 2^2) NOT (3^2 + 1 + 1 + 1)
n = 6, return 3 (4 + 1 + 1) = (2^2 + 1^2 + 1^2)
*/
class MinimumPerfectSquares {
   public:
    static void test() {
        int n = 12;
        vector<int> dp(n + 1, -1);
        int cnt = minPerfectSquares(n, dp);
        cout << format("Minimum number of perfect squares {} needed to reach target sum {}", cnt, n) << endl;
    }

    static int minPerfectSquares(int n, vector<int>& dp) {
        if (n < 0) return INT_MAX;
        if (n == 0) return 0;
        if (dp[n] != -1) return dp[n];

        int i = 1;
        int cur = INT_MAX;
        while (i * i <= n) {
            int val = minPerfectSquares(n - i * i, dp);
            if (val != INT_MAX) cur = min(cur, val + 1);
            i++;
        }

        dp[n] = cur;

        return dp[n];
    }

   private:
    int num_squares(int n) {
        int table[n + 1];
        int max = floor(sqrt(n));
        int squared;

        for (int i = 0; i <= n; i++) {
            table[i] = i;
        }
        for (int i = 2; i <= max; i++) {
            for (int j = 0; j <= n; j++) {
                squared = pow(i, 2);
                if (squared <= j)
                    table[j] = min(table[j], table[j - squared] + 1);
            }
        }
        return table[n];
    }

    int numSquares(int n) {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};