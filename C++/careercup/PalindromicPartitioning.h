#pragma once
#include "../header.h"

class PalindromicPartitioning {
   public:
    static void test() {
    }

    vector<vector<string>> partition(const string& str) {
        vector<vector<string>> result;
        vector<vector<bool>> dp;

        for (int l = 1; l <= str.length(); l++) {
            for (int i = 0; i < l; i++) {
                int j = i + l - 1;
                if (l == 1 || (l == 2 && str[i] == str[j])) dp[i][j] = true;
                else if (str[i] == str[j] && dp[i + 1][j - 1]) dp[i][j] = true;
                else dp[j][j + l - 1] = false;
            }
        }

        dfs(0, str, dp, result, {});
    }

    void dfs(int i, const string& str, vector<vector<bool>>& dp, vector<vector<string>>& result, vector<string> tmp) {
        if (i >= str.length()) {
            result.push_back(tmp);
            return;
        }

        for (int j = i; j < str.length(); j++) {
            if (dp[i][j]) {
                tmp.push_back(str.substr(i, j - i + 1));
                dfs(i + 1, str, dp, result, tmp);
                tmp.pop_back();
            }
        }
    }
};