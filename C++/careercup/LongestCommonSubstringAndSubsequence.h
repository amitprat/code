#pragma once
#include "../Header.h"

class LongestCommonSubstringAndSubsequence {
   public:
    static void test() {
        {
            string str1 = "AGGTAB";
            string str2 = "GXTXAYB";

            {
                int l1 = longestCommonSubsequenceRec(str1, str1.length(), str2, str2.length());
                string l2 = longestCommonSubsequenceDP(str1, str1.length(), str2, str2.length());

                assert(l1 == l2.length());

                cout << format("Longest common subsequence for str1={} and str2={} is length={}, str={}", str1, str2, l1, l2) << endl;
            }

            {
                int l1 = longestCommonSubstringRec(str1, str1.length(), str2, str2.length(), 0);
                int l2 = longestCommonSubstringDP(str1, str1.length(), str2, str2.length());

                assert(l1 == l2);

                cout << format("Longest common substring for str1={} and str2={} is length={}", str1, str2, l1) << endl;
            }
        }

        {
            string str1 = "abc";
            string str2 = "abc";

            int l1 = longestCommonSubsequenceRec(str1, str1.length(), str2, str2.length());
            string l2 = longestCommonSubsequenceDP(str1, str1.length(), str2, str2.length());

            assert(l1 == l2.length());

            cout << format("Longest common subsequence for str1={} and str2={} is length={}, str={}", str1, str2, l1, l2) << endl;
        }

        {
            string str1 = "abc";
            string str2 = "cba";

            int l1 = longestCommonSubsequenceRec(str1, str1.length(), str2, str2.length());
            string l2 = longestCommonSubsequenceDP(str1, str1.length(), str2, str2.length());

            assert(l1 == l2.length());

            cout << format("Longest common subsequence for str1={} and str2={} is length={}, str={}", str1, str2, l1, l2) << endl;
        }

        {
            string str1 = "abcdec";
            string str2 = "acecfg";

            int l1 = longestCommonSubsequenceRec(str1, str1.length(), str2, str2.length());
            string l2 = longestCommonSubsequenceDP(str1, str1.length(), str2, str2.length());

            assert(l1 == l2.length());

            cout << format("Longest common subsequence for str1={} and str2={} is length={}, str={}", str1, str2, l1, l2) << endl;
        }

        {
            string str1 = "AGGTAB";
            string str2 = "GXTXAYB";

            int l1 = longestCommonSubstringRec(str1, str1.length(), str2, str2.length(), 0);
            int l2 = longestCommonSubstringDP(str1, str1.length(), str2, str2.length());

            assert(l1 == l2);

            cout << format("Longest common substring for str1={} and str2={} is length={}", str1, str2, l1) << endl;
        }
    }

   private:
    static int longestCommonSubsequenceRec(string a, int n, string b, int m) {
        if (n == 0 || m == 0) return 0;

        if (a[n - 1] == b[m - 1]) return 1 + longestCommonSubsequenceRec(a, n - 1, b, m - 1);

        return max(longestCommonSubsequenceRec(a, n - 1, b, m), longestCommonSubsequenceRec(a, n, b, m - 1));
    }

    static string longestCommonSubsequenceDP(string a, int n, string b, int m) {
        vector<vector<int>> table(n + 1, vector<int>(m + 1));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else if (a[i - 1] == b[j - 1])
                    table[i][j] = 1 + table[i - 1][j - 1];
                else
                    table[i][j] = max(table[i - 1][j], table[i][j - 1]);
            }
        }

        string res;
        int i = n, j = m;
        while (table[i][j] > 0) {
            if (i == 0) {
                j--;
            } else if (j == 0) {
                i--;
            } else if (a[i - 1] == b[j - 1]) {
                res += a[i - 1];
                i--;
                j--;
            } else if (table[i - 1][j] > table[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        std::reverse(res.begin(), res.end());

        return res;
    }

   private:
    static int longestCommonSubstringRec(string a, int n, string b, int m, int len) {
        if (n == 0 || m == 0) return len;

        // count including
        int countIncluding = 0;
        if (a[n - 1] == b[m - 1]) countIncluding = longestCommonSubstringRec(a, n - 1, b, m - 1, len + 1);

        int countExcluding = max(longestCommonSubstringRec(a, n - 1, b, m, 0), longestCommonSubstringRec(a, n, b, m - 1, 0));

        return max(countIncluding, countExcluding);
    }

    static int longestCommonSubstringDP(string a, int n, string b, int m) {
        vector<vector<int>> table(n + 1, vector<int>(m + 1));

        int result = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                table[i][j] = 0;
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else if (a[i - 1] == b[j - 1])
                    table[i][j] = 1 + table[i - 1][j - 1];
                result = max(result, table[i][j]);
            }
        }

        return result;
    }
};