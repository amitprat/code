#pragma once
#include "../header.h"

/*
Given an array of strings with only lowercase letters , create a function that returns an array of those same strings,
but each string has its letters rearranged such that it becomes a palindrome (if possible, if not, return -1)
*/

class RearrangeCharsToMakeStringPalindromic {
   public:
    pair<bool, string> makePalin(char word[], int n) {
        string res;

        int count[26] = {0};
        for (int i = 0; i < n; i++) count[word[i] - 'a']++;

        int oddCount = 0;
        char oddChar;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            if (!(count[ch - 'a'] & 1)) {
                int cnt = count[ch - 'a'];
                res += string(cnt / 2, ch);
            } else {
                oddChar = ch;
                oddCount++;
                if (oddCount > 1) return {false, ""};
            }
        }

        res = res + oddChar + res;

        return {true, res};
    }
};