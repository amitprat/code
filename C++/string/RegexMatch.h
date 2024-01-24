#pragma once
#include "../Header.h"

class RegexMatch {
public:
    static void test() {
        RegexMatch obj;
        assert(obj.isMatch("a*", "") == true);
        assert(obj.isMatch(".", "") == false);
        assert(obj.isMatch("ab*", "a") == true);
        assert(obj.isMatch("a.", "ab") == true);
        assert(obj.isMatch("a", "a") == true);

        assert(obj.isMatchDP("a*", "") == true);
        assert(obj.isMatchDP(".", "") == false);
        assert(obj.isMatchDP("ab*", "a") == true);
        assert(obj.isMatchDP("a.", "ab") == true);
        assert(obj.isMatchDP("a", "a") == true);
    }

    bool isMatch(string pat, string txt) {
        return isMatch(txt, pat, txt.length(), pat.length());
    }

    bool isMatch(string txt, string pat, int n, int m) {
        if (m == 0) return n == 0;
        if (n == 0) return pat[m - 1] == '*' && isMatch(txt, pat, n, m - 2);

        if (txt[n - 1] == pat[m - 1] || pat[m - 1] == '.') return isMatch(txt, pat, n - 1, m - 1);
        if (pat[m - 1] == '*') {
            return isMatch(txt, pat, n, m - 2) ||
                (m > 2 && (txt[n - 1] == pat[m - 2] || pat[m - 2] == '.')) && isMatch(txt, pat, n - 1, m);
        }
        return false;
    }

    bool isMatchDP(string pat, string txt) {
        int n = txt.length();
        int m = pat.length();
        vector<vector<bool>> table(n + 1, vector<bool>(m + 1));
        table[0][0] = true; // if both txt and pat are empty
        for (int i = 1; i <= n; i++) { // if pat is empty
            table[i][0] = false;
        }

        if (m > 0)table[0][1] = false;
        for (int j = 2; j <= m; j++) { // if txt is empty
            table[0][j] = pat[j - 1] == '*' ? true : false;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (txt[i - 1] == pat[j - 1] || pat[j - 1] == '.') table[i][j] = table[i - 1][j - 1];
                else if (pat[j - 1] == '*' && j >= 2)
                    table[i][j] = (txt[i - 1] == pat[j - 2] || pat[j - 2] == '.')
                    ? table[i][j - 2] || table[i - 1][j] : false;
                else table[i][j] = false;
            }
        }

        return table[n][m];
    }
};