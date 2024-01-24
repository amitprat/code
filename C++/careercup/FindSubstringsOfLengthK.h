#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5682825644736512

Given string say ABCGRETCABCG and substring length let us take length as 3, find the count of possible substrings, for example in
above string ABC => 2 and BCG => 2 , where CGR and other 3 word length substrings has a count of 1.
*/
class FindSubstringsOfLengthK
{
public:
    static void test()
    {
        string str = "ABCGRETCABCG";
        int k = 3;

        printSubstringsOfLength(str, k);
    }

    static void printSubstringsOfLength(string str, int k)
    {
        unordered_map<string, int> substrs;

        int n = str.length();
        for (int i = 0; i <= n - k; i++) {
            string cur = str.substr(i, k);
            substrs[cur]++;
        }

        cout << to_string(substrs) << endl;
    }
};