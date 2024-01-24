#pragma once
#include "../header.h"

class LongestUniqueSubstr
{
public:
    static void test()
    {
        LongestUniqueSubstr obj;
        vector<string> strs = { "", "a","abcabcbb", "bbbbb", "pwwkew","abbcdef" };
        for (auto str : strs) {
            cout << obj.longest(str) << endl;
        }
    }

    string longest(string str)
    {
        string res;
        vector<int> lastIndex(256, -1);
        int s = 0;
        for (int e = 0; e < str.size(); e++) {
            s = max(s, lastIndex[str[e]] + 1);
            if (e - s + 1 > res.size()) res = str.substr(s, e - s + 1);
            lastIndex[str[e]] = e;
        }

        return res;
    }
};