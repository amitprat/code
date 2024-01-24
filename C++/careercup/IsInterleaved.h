#pragma once
#include "../Header.h"

class CheckIfStringIsInterleaved {
   public:
    static void test() {
        {
            string a = "abcd";
            string b = "xyz";
            string c = "axybczd";

            {
                bool res = isInterleaved(a, b, c);
                cout << format("c='{}' is interleaved by a='{}' and b='{}', res(using DP)? {}", c, a, b, res) << endl;
            }

            {
                bool res = isInterleaved(a, a.length(), b, b.length(), c, c.length());
                cout << format("c='{}' is interleaved by a='{}' and b='{}', res(using recursion)? {}", c, a, b, res) << endl;
            }

            {
                bool res = isInterleavedDP2(a, b, c);
                cout << format("c='{}' is interleaved by a='{}' and b='{}', res(using DP2)? {}", c, a, b, res) << endl;
            }
        }

        {
            string a = "dabc";
            string b = "xyz";
            string c = "abxcyzd";

            {
                bool res = isInterleaved(a, b, c);
                cout << format("c='{}' is interleaved by a='{}' and b='{}', res(using DP)? {}", c, a, b, res) << endl;
            }

            {
                bool res = isInterleaved(a, a.length(), b, b.length(), c, c.length());
                cout << format("c='{}' is interleaved by a='{}' and b='{}', res(using recursion)? {}", c, a, b, res) << endl;
            }

            {
                bool res = isInterleavedDP2(a, b, c);
                cout << format("c='{}' is interleaved by a='{}' and b='{}', res(using DP2)? {}", c, a, b, res) << endl;
            }
        }
    }

    static bool isInterleaved(string a, int l, string b, int m, string c, int n) {
        if (l == 0 && m == 0 && n == 0) return true;
        if (l < 0 || m < 0 || n <= 0) return false;

        return (l > 0 && a[l - 1] == c[n - 1] && isInterleaved(a, l - 1, b, m, c, n - 1)) ||
               (m > 0 && b[m - 1] == c[n - 1] && isInterleaved(a, l, b, m - 1, c, n - 1));
    }

    static bool isInterleaved(string a, string b, string c) {
        int n = a.length();
        int m = b.length();
        vector<vector<bool>> memo(n + 1, vector<bool>(m + 1, false));

        for (int i = 0; i <= a.size(); i++) {
            for (int j = 0; j <= b.size(); j++) {
                if (i == 0 && j == 0)
                    memo[i][j] = true;
                else if (i == 0)
                    memo[i][j] = (c[i + j - 1] == b[j - 1]);
                else if (j == 0)
                    memo[i][j] = (c[i + j - 1] == a[i - 1]);
                else if (c[i + j - 1] == a[i - 1] || c[i + j - 1] == b[j - 1]) {
                    if (c[i + j - 1] == a[i - 1]) memo[i][j] = memo[i][j] || memo[i - 1][j];
                    if (c[i + j - 1] == b[j - 1]) memo[i][j] = memo[i][j] || memo[i][j - 1];
                }
            }
        }

        return memo[n][m];
    }

    static bool isInterleavedDP2(string a, string b, string c) {
        int n = a.length();
        int m = b.length();

        vector<vector<int>> table(n + 1, vector<int>(m + 1, false));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0)
                    table[i][j] = true;
                else if (i == 0)
                    table[i][j] = (c[i + j - 1] == b[j - 1] && table[i][j - 1]);
                else if (j == 0)
                    table[i][j] = (c[i + j - 1] == a[i - 1] && table[i - 1][j]);
                else if (c[i + j - 1] == a[i - 1] || c[i + j - 1] == b[j - 1])
                    table[i][j] = table[i - 1][j] || table[i][j - 1];
            }
        }

        return table[n][m];
    }
};