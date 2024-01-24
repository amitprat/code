#pragma once
#include "../Header.h"

class CheckRepeatedSubsequence {
public:
    static void test() {
        string str = "abba";
        auto res = isRepeatedSubsequence(str);
        cout << "Is repeated ? " << res << endl;

        string str1 = "abab";
        auto res1 = isRepeatedSubstring(str1);
        cout << "Is repeated substring ? " << res1 << endl;
    }

    static bool isRepeatedSubsequence(string str) {
        int n = str.size();
        vector<vector<int>> table(n + 1, vector<int>(n + 1));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                table[i][j] = 0;
                if (i != 0 && j != 0) {
                    if (i != j && str[i - 1] == str[j - 1]) table[i][j] = 1 + table[i - 1][j - 1];
                    else table[i][j] = max(table[i - 1][j], table[i][j - 1]);
                }
            }
        }

        return table[n][n] > 1;
    }

    static bool isRepeatedSubstring(string str) {
        int n = str.length();
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string first = str.substr(0, i);
                int j = i;
                while (j + i <= n) {
                    string next = str.substr(j, i);
                    if (first != next) break;
                    j += i;
                }
                if (j == n) {
                    cout << "period =" << first << endl;
                    return true;
                }
            }
        }
        return false;
    }
};