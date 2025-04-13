#pragma once
#include "../header.h"

class LongestSubstrWithoutRepeatingChars {
   public:
    static void test() {
        string s = "geeksforgeeks";
        cout << "The input String is " << s << endl;
        string longest1 = longestUniqueSubstr(s);
        string longest2 = longestUniqueSubstr2(s);

        cout << "The length of the longest non-repeating character "
             << "substring is "
             << longest1;
    }

   public:
    static string longestUniqueSubstr(string str) {
        int* visited = new int[26];
        memset(visited, -1, sizeof(bool) * 26);
        int s = 0;
        string longest = "";
        for (int e = 0; e < str.length(); e++) {
            int index = str[e] - 'a';
            if (visited[index] != -1) {
                longest = maxSubstr(longest, str.substr(s, e - s));
                while (s <= visited[index]) {
                    int oldIndex = str[s] - 'a';
                    visited[oldIndex] = false;
                    s++;
                }
            }
            visited[index] = e;
        }

        return longest;
    }

    static string maxSubstr(string x, string y) {
        return x.length() > y.length() ? x : y;
    }

   public:
    static string longestUniqueSubstr2(const string& str) {
        pair<int, int> maxPos = {0, -1};
        vector<int> lastPos(256, -1);
        int i = 0;
        int j = 0;
        while (j < str.length()) {
            i = max(i, lastPos[str[j]] + 1);
            if (j - i > maxPos.second - maxPos.first) {
                maxPos = {i, j};
            }
            lastPos[str[j]] = j;

            j++;
        }

        return str.substr(maxPos.first, maxPos.second - maxPos.first + 1);
    }

   public:
    static int lengthOfLongestSubstring(const string& str) {
        unordered_map<char, int> lastPos;

        int res = 0;

        int s = 0, e = 0;
        while (e < str.length()) {
            if (lastPos.find(str[e]) == lastPos.end())
                lastPos[str[e]] = e;
            else {
                int cur = e - s;
                res = max(res, cur);

                while (s <= lastPos[str[e]]) {
                    lastPos.erase(str[s]);
                    s++;
                }

                lastPos[str[e]] = e;
            }

            e++;
        }

        res = max(res, e - s);

        return res;
    }
};