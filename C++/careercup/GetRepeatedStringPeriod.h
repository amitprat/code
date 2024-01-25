#pragma once
#include "../Header.h"
/*
Find whether string S is periodic.
Periodic indicates S = nP.
e.g.
S = "ababab", then n = 3, and P = "ab"
S = "xxxxxx", then n = 1, and P = "x"
S = "aabbaaabba", then n = 2, and P = "aabba"
follow up:
Given string S, find out the P (repetitive pattern) of S.
*/

class GetRepeatedStringPeriod {
   public:
    static void test() {
        vector<string> strs = {"waterwater", "ababab", "xxxxxx", "aabbaaabba", "abcd", "dbcasdssddbcasds"};
        GetRepeatedStringPeriod obj;

        for (auto str : strs) {
            auto res1 = obj.isPeriod1(str);
            auto res2 = obj.isPeriod1(str);
            assert(res1 == res2);

            cout << "Is string='" << str << "' periodic: " << res1 << endl;

            if (res1) {
                auto period1 = obj.getPeriod1(str);
                auto period2 = obj.getPeriod2(str);
                assert(period1 == period2);

                cout << format("Period={}, Repeated={}", period1.first, period1.second) << endl;
            }

            cout << endl;
        }
    }

   private:
    bool isPeriod1(string str) {
        return (str.substr(1) + str.substr(0, str.length() - 1)).find(str) != string::npos;
    }

    pair<string, int> getPeriod1(string str) {
        int n = str.length();
        for (int i = 1; i <= n / 2; i++) {
            if (n % i == 0) {
                string period = str.substr(0, i);
                int j = i;
                while (j + i <= n) {
                    if (str.substr(j, i) != period) break;

                    j += i;
                    if (j == n) return {period, n / i};
                }
            }
        }
        return {"", -1};
    }

   private:
    bool isPeriod2(string s) {
        string tmp = s + s;
        tmp = tmp.substr(1, tmp.length() - 2);
        return (tmp.find(s) != string::npos);
    }

    pair<string, int> getPeriod2(string s) {
        int n = s.length();
        for (int len = 1; len <= n / 2; len++) {
            if (n % len == 0 && isRepeat(s, len, n)) {
                return {s.substr(0, len), n / len};
            }
        }
        return {"", -1};
    }

    bool isRepeat(string s, int periodLen, int totalLen) {
        for (auto i = 0; i < periodLen; i++) {
            for (int j = periodLen + i; j < totalLen; j += periodLen) {
                if (s[i] != s[j]) return false;
            }
        }
        return true;
    }
};
