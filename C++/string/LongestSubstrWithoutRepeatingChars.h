#pragma once
#include "../header.h"

class LongestSubstrWithoutRepearingChars {
public:
    static void test() {
        string s = "geeksforgeeks";
        cout << "The input String is " << s << endl;
        string longest = longestUniqueSubsttr(s);

        cout << "The length of the longest non-repeating character "
            << "substring is "
            << longest;
    }

    static string longestUniqueSubsttr(string str) {
        int* visited = new int[26];
        memset(visited, -1, sizeof(bool) * 26);
        int s = 0;
        string longest = "";
        for (int e = 0; e < str.length(); e++) {
            int index = str[e] - 'a';
            if (visited[index] != -1) {
                longest = maxSubstr(longest, str.substr(s, e - s));
                int newStart = visited[index];
                while (s <= newStart) {
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
};