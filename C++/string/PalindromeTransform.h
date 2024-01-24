#pragma once
#include "../Header.h"

class PalindromeTransform
{
public:
    static void test()
    {
        PalindromeTransform obj;
        cout << obj.ModifiedEditDistance("abxa", "axba", 1) << endl;  // 2 <= 2*1 - YES
        cout << obj.ModifiedEditDistance("abdxa", "axdba", 1) << endl; // 4 > 2*1 - NO
        cout << obj.ModifiedEditDistance("abaxbabax", "xababxaba", 2) << endl; // 4 <= 2*2 - YES
    }

    int ModifiedEditDistance(string a, string b, int k) {
        int n = a.length();
        int m = b.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        dp[0][0] = 0;
        for (int j = 1; j <= m; j++) dp[0][j] = j;
        for (int i = 1; i <= n; i++) dp[i][0] = i;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
                else dp[i][j] = 1 + min(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[n][m];
    }
};