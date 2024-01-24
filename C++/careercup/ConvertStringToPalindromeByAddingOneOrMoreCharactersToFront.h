#pragma once
#include "../Header.h"

/*
* https://www.careercup.com/question?id=6218545979457536
Given a string S, you are allowed to convert it to a palindrome by adding 0 or more characters in front of it.
Find the length of the shortest palindrome that you can create from S by applying the above transformation.

The thing is, the time complexity gets reduced by simply finding palindrome that start from first character. If we reduce the suffix tree implementation:

1. Create suffix tree from the reverse string (Ukkonen proved this is O(n))
2. Walk this tree from the beginning with the original string until there is path.

This is largest palindrome that starts with beginning. So you need to add [original string length] - [found polyndrome] characters in the front
*/
class ConvertStringToPalindromeByAddingOneOrMoreCharactersToFront
{
public:
    static void test()
    {
        string s = "BABABAA";

        int res = calculate(s);
    }

    static int calculate(string s)
    {
        int cnt = 0;
        for (int j = s.length() - 1; j >= 1; j--) {
            if (isPalin(s, 0, j)) return cnt;
            cnt++;
        }

        return cnt;
    }

    static bool isPalin(string str, int s, int e) {
        while (s < e) {
            if (str[s] != str[e]) return false;
            s++;
            e--;
        }
        return true;
    }

    int getMinCharToAddedToMakeStringPalin(string str)
    {
        string rev = str;
        reverse(rev.begin(), rev.end());

        string concat = str + "$" + rev;
        vector<int> lps = getLps(concat);

        return str.length() - lps.back();
    }

    vector<int> getLps(string str)
    {
        vector<int> lps(str.length(), 0);
        int len = 0;
        lps[0] = len;

        int i = 0;
        while (i < str.length()) {
            if (str[i] == str[len]) {
                len++;
                lps[i++] = len;
            }
            else {
                if (len != 0) {
                    len = lps[len - 1];
                }
                else {
                    lps[i++] = 0;
                }
            }
        }

        return lps;
    }
};