#pragma once
#include "../Header.h"

class CountPalindromes {
public:
    static void test() {
        string str = "abba";

        auto res = countPalin(str);
        cout << "Palindromes = " << res << endl;
    }

    static int countPalin(string str) {
        int n = str.length();
        vector<vector<bool>> table(n, vector<bool>(n, false));
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            cnt++;
            table[i][i] = false;
        }

        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n - l + 1; i++) {
                int j = i + l - 1;

                if (l == 2 && str[i] == str[j]) {
                    table[i][j] = true;
                    cnt++;
                    continue;
                }

                if (table[i + 1][j - 1] && str[i] == str[j]) {
                    table[i][j] = true;
                    cnt++;
                }
            }
        }

        return cnt;
    }
};