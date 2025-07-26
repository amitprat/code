#pragma once
#include "../header.h"

/*
* https://leetcode.com/problems/isomorphic-strings/description/?envType=study-plan-v2&envId=top-interview-150

Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:
Input: s = "egg", t = "add"
Output: true

Explanation:
The strings s and t can be made identical by:

Mapping 'e' to 'a'.
Mapping 'g' to 'd'.
*/
class IsomorphicStrings {
   public:
    bool isIsomorphic(string s, string t) {
        auto color1 = colorDistribute(s);
        auto color2 = colorDistribute(t);

        return color1 == color2;
    }

    string colorDistribute(const string& str) {
        string result;

        unordered_map<char, int> m;
        int cnt = 0;
        for (auto& ch : str) {
            if (!m.contains(ch)) m[ch] = cnt++;
            result += m[ch];
        }
        return result;
    }
};