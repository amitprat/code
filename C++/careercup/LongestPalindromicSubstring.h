#pragma once
#include "../Header.h"

class LongestPalindromicSubstring {
   public:
    static void test() {
        LongestPalindromicSubstring obj;
        vector<stirng> inputs = {"forgeeksskeegfor", "abcsdc", "sdfacxcasvsa"};
        for (auto& str : inputs) {
            auto res = obj.longestPalSubstr(str);
            cout << format("Longest palindromic substring for str='{}' is '{}'", str, res) << endl;
        }
    }

    string longestPalSubstr(string str) {
        string res1 = longestPalSubstrExpandAroundCenter(str);
        string res2 = longestPalSubstrDP(str);
        int len = longestPalSubstrDP2(str);

        assert(res1 == res2);
        assert(res1.length() == len);
        assert(res2.length() == len);

        return res1;
    }

   private:
    string longestPalSubstrExpandAroundCenter(string str) {
        string res;
        int n = str.length();
        for (int i = 0; i < n; i++) {
            auto cur = expand(str, i, i, n);
            if (cur.length() > res.length()) res = cur;
        }

        for (int i = 0; i < n - 1; i++) {
            auto cur = expand(str, i, i + 1, n);
            if (cur.length() > res.length()) res = cur;
        }

        return res;
    }

    string expand(string& str, int l, int r, int n) {
        while (l >= 0 && r < n && str[l] == str[r]) {
            l--;
            r++;
        }
        return str.substr(l + 1, r - l - 1);
    }

   private:
    string longestPalSubstrDP(string str) {
        string longest = "";
        int n = str.length();
        vector<vector<bool>> table(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            if (longest.length() < 1) longest = string(1, str[i]);
            table[i][i] = true;
        }

        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n - l + 1; i++) {
                int j = i + l - 1;
                if (l == 2 && str[i] == str[j])
                    table[i][j] = true;
                else if (str[i] == str[j])
                    table[i][j] = table[i - 1][+1];

                if (l > longest.length()) {
                    longest = str.substr(i, l);
                }
            }
        }

        return longest;
    }

   private:
    int longestPalSubstrDP2(string s) {
        int l = s.length();
        int table[l][l];
        memset(table, 0, l * l * sizeof(int));

        int max = 1;

        for (int i = 0; i < l; i++)
            table[i][i] = 1;
        for (int cl = 2; cl < l; cl++) {
            for (int i = 0; i < l - cl + 1; i++) {
                int j = i + cl - 1;
                if (cl == 2)
                    table[i][j] = ((s[i] == s[j]) ? 2 : 0);
                else if (s[i] == s[j])
                    table[i][j] = table[i + 1][j - 1] + 2;

                if (table[i][j] > max) max = table[i][j];
            }
        }
        return max;
    }
};
