#pragma once
#include "../header.h"

/*
https://leetcode.com/problems/minimum-window-substring/?envType=study-plan-v2&envId=top-interview-150

Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.



Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
*/

class MinimumWindowSubstring {
   public:
    static void test() {
        MinimumWindowSubstring obj;
        string s = "ADOBECODEBANC";
        string t = "ABC";
        string expected = "BANC";

        string res = obj.minWindow2(s, t);
        assert(expected == res);
        cout << format("Minimum window of s={} which contains all characters from t={} is {}", s, t, res) << endl;
    }

   private:
    string minWindow(string str, string t) {
        int tHash[256] = {0};
        int curHash[256] = {0};
        for (auto& ch : t) tHash[ch]++;

        int count = 0;
        int mnLen = INT_MAX;
        string result;

        for (int s = 0, e = 0; e < str.length(); e++) {
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
            }
        }

        return result;
    }

   private:
    string minWindow2(string& str, string& pat) {
        vector<int> patCnt(26, 0);
        vector<int> strCnt(26, 0);
        for (auto& ch : pat) patCnt[ch]++;

        int patLen = pat.length();
        int len = 0;
        int minWindoLenth = INT_MAX;
        int minWindowStart = 0;

        int index = 0;
        int start = 0;
        for (auto ch : str) {
            strCnt[ch]++;
            index++;
            if (strCnt[ch] <= patCnt[ch]) len++;

            while (len == patLen) {
                if (index - start + 1 < minWindoLenth) {
                    minWindoLenth = index - start + 1;
                    minWindowStart = start;
                }

                char left = str[start++];
                if (strCnt[left] <= patCnt[left]) len--;
                strCnt[left]--;
            }
        }

        return str.substr(minWindowStart, minWindoLenth);
    }

   public:
    string minWindow3(string str, string t) {
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

   public:
    string minWindow4(string s, string t) {
        vector<int> sCnt(256, 0);
        vector<int> tCnt(256, 0);

        int l = t.length();
        for (auto& ch : t) tCnt[ch]++;

        int curLen = 0;
        pair<int, int> minWin = {0, INT_MAX};
        for (int start = 0, end = 0; end < s.length(); end++) {
            char ch = s[end];
            sCnt[ch]++;
            if (sCnt[ch] <= tCnt[ch]) curLen++;

            if (curLen == l) {
                while (start <= end && sCnt[s[start]] > tCnt[s[start]]) {
                    sCnt[s[start]]--;
                    start++;
                }
                if (minWin.second > end - start + 1) minWin = {start, end - start + 1};
                sCnt[s[start]]--;
                start++;
                curLen--;
            }
        }

        return minWin.second == INT_MAX ? "" : s.substr(minWin.first, minWin.second);
    }

   public:
    string minWindow(string_view str, string_view pat) {
        if (str.empty() || pat.empty() || str.size() < pat.size()) return {};

        array<int, 256> freq{};
        for (unsigned char c : pat) freq[c]++;

        int required = static_cast<int>(pat.size());
        int matched = 0;
        size_t minStart = 0, minLen = string_view::npos;

        for (size_t s = 0, e = 0; e < str.size(); ++e) {
            if (freq[static_cast<unsigned char>(str[e])]-- > 0) ++matched;

            while (matched == required) {
                if (auto len = e - s + 1; len < minLen || minLen == string_view::npos) {
                    minLen = len;
                    minStart = s;
                }
                if (++freq[static_cast<unsigned char>(str[s++])] > 0) --matched;
            }
        }

        return minLen == string_view::npos ? "" : string(str.substr(minStart, minLen));
    }
};