#pragma once
#include "../Header.h"

class LongestPalin {
public:
    static void test() {
        LongestPalin obj;
        string str = "GEEKS FOR GEEKS";
        cout << "Longest Palin Subsequence Recursive =" << obj.longestRec(str, 0, str.length() - 1) << endl;
        cout << "Longest Palin Subsequence =" << obj.longest(str) << endl;
    }

    int longestRec(string str, int l, int r) {
        if (l > r) return 0;
        if (l == r) return 1;

        if (str[l] == str[r]) return 2 + longestRec(str, l + 1, r - 1);
        return max(longestRec(str, l + 1, r), longestRec(str, l, r - 1));
    }

    int longest(string str) {
        int n = str.length();
        vector<vector<int>> table(n, vector<int>(n, 0));

        for (int k = 1; k <= n; k++) {
            for (int i = 0; i < n - k + 1; i++) {
                int j = i + k - 1;
                if (i == j) table[i][j] = 1; // palin size=1
                else if (i + 1 == j) table[i][j] = 1 + (str[i] == str[j]); // palin size=2
                else { // size > 2
                    table[i][j] = max(table[i + 1][j], table[i][j - 1]);
                    if (str[i] == str[j])
                        table[i][j] = max(table[i][j], 2 + table[i + 1][j - 1]);
                }
            }
        }

        cout << to_string(table) << endl;

        return table[0][n - 1];
    }
};