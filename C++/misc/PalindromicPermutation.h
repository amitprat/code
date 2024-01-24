#pragma once
#include "../Header.h"
using namespace std;

class PalindromicPermutation
{
public:
    static void test()
    {
        PalindromicPermutation obj;
        vector<string> strs = { "abcbcac", "","a", "ab", "aba", "abac", "abdcab" };
        for (auto& str : strs) {
            auto res1 = obj.IsPalinPerm(str);
            auto res2 = obj.IsPalinPermOptimized(str);
            assert(res1 == res2);

            cout << "Is palin : " << str << " : " << res1 << endl;
        }
    }

    bool IsPalinPerm(string str)
    {
        int table[26] = { 0 };
        int oddCount = 0;
        for (auto ch : str) {
            table[ch - 'a']++;
            if (table[ch - 'a'] & 1) oddCount++;
            else oddCount--;
        }

        return oddCount <= 1;
    }

    bool IsPalinPermOptimized(string str)
    {
        int oddCount = 0;
        bitset<26> bitset;
        for (auto ch : str) {
            bitset.flip(ch - 'a');
            //bitset.set(ch - 'a', !bitset[ch - 'a']);
            if (bitset[ch - 'a']) oddCount++;
            else oddCount--;
        }

        return oddCount <= 1;
    }
};