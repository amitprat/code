#pragma once
#include "../header.h"

class MinimumWindowSubstring {
   public:
    static void test() {
        MinimumWindowSubstring obj;
        string s = "ADOBECODEBANC";
        string t = "ABC";
        string expected = "BANC";
        string cur = obj.minWindow(s, t);
        cout << "Min Windows : " << cur << endl;
        assert(expected == cur);
    }

    string minWindow(string str, string t) {
        int tHash[256] = {0};
        int curHash[256] = {0};
        for (auto& ch : t) tHash[ch]++;
        int count = 0;
        int s = 0;
        int mnLen = INT_MAX;
        string result;

        for (int e = 0; e < str.length(); e++) {
            char ch = str[e];
            curHash[ch]++;
            if (curHash[ch] <= tHash[ch]) count++;
            if (count == t.length()) {
                ch = str[s];
                while (tHash[ch] == 0 || curHash[ch] > tHash[ch]) {
                    if (curHash[ch] > tHash[ch]) {
                        curHash[ch]--;
                    }
                    s++;
                    ch = str[s];
                }
                if (e - s + 1 < mnLen) {
                    mnLen = e - s + 1;
                    result = str.substr(s, e - s + 1);
                }
                curHash[str[s]]--;
                count--;
                s++;
            }
        }

        return result;
    }
};