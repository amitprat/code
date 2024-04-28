#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=5684278553739264

Given s string, Find max size of a sub-string, in which no duplicate chars present.
*/

class SubstringWithNoDuplicateChars {
   public:
    string getSubstr(string& str) {
        unordered_map<char, int> charMap;
        string maxStr;
        int maxLen = 0;
        int s = 0, e = 0;
        for(auto ch : str) {
            if(charMap.find(ch) == charMap.end()) {
                e++;
            } else {
                string curMax = str.substr(s, e-s);
                if(e-s > maxLen) {
                    maxLen = e-s;
                    maxStr = curMax;
                }
                int lastPos = charMap[ch];
            }
            charMap[ch] = e++;
        }

        if(e-s > maxLen) {
            maxStr = str.substr(s, e-s);
        }

        return maxStr;
    }
};