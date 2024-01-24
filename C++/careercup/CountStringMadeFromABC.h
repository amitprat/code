#pragma once
#include "../Header.h"

class CountStringMadeFromABC {
public:
    static void test() {
        int b = 1, c = 2, n = 3;
        int res = count(b, c, n);
        cout << res << endl;
    }

    static int count(int b, int c, int n) {
        if (b < 0 || c < 0) return 0;
        if (n == 0) return 1;

        return count(b, c, n - 1) + count(b - 1, c, n - 1) + count(b, c - 1, n - 1);
    }

    static int countDP(int b, int c, int n) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(b + 1, vector<int>(c + 1)));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= b; j++) {
                for (int k = 0; k <= c; k++) {
                    if (i == 0) dp[i][j][k] = 1;
                    else {
                        dp[i][j][k] += dp[i - 1][j][k];
                        if (j > 0) dp[i][j][k] += dp[i - 1][j - 1][k];
                        if (k > 0) dp[i][j][k] += dp[i - 1][j][k - 1];
                    }
                }
            }
        }

        return dp[n][b][c];
    }
};