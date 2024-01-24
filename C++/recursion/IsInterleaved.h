#pragma once
#include "../header.h"

class IsInterleaved {
public:
    static void test() {
        IsInterleaved obj;
        vector<tuple<string, string, string>> inputs = {
            {"XXY", "XXZ", "XXZXXXY"},
            {"XY", "WZ", "WZXY"},
            {"XY", "X", "XXY"},
            {"YX", "X", "XXY"},
            {"XXY", "XXZ", "XXXXZY"}
        };
        for (auto input : inputs) {
            cout << "IsInterleaved = " << obj.test(get<0>(input), get<1>(input), get<2>(input)) << endl;
        }
    }

    bool test(string a, string b, string c, int n, int m) {
        if (n == 0 && m == 0) return true;
        if (n < 0 || m < 0) return false;
        if (n == 0) return c.substr(0, m) == b.substr(0, m);
        if (m == 0) return c.substr(0, n) == a.substr(0, n);
        if (a[n - 1] != c[n + m - 1] && b[m - 1] != c[n + m - 1]) return false;
        return test(a, b, c, n - 1, m) || test(a, b, c, n, m - 1);
    }

    bool test(string a, string b, string c) {
        int n = a.length();
        int m = b.length();
        vector<vector<bool>> table(n + 1, vector<bool>(m + 1, false));

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 && j == 0) {
                    table[i][j] = true;
                }
                else if (i == 0 || j == 0) {
                    table[i][j] = (i == 0 ? b[j - 1] == c[j - 1] : a[i - 1] == c[i - 1]);
                }
                else if (a[i - 1] == c[i + j - 1]) {
                    table[i][j] = table[i - 1][j];
                }
                else if (b[j - 1] == c[i + j - 1]) {
                    table[i][j] = table[i][j - 1];
                }
                else if (a[i - 1] == c[i + j - 1] || b[j - 1] == c[i + j - 1]) {
                    table[i][j] = table[i - 1][j] || table[i][j - 1];
                }
            }
        }

        return table[n][m];
    }
};