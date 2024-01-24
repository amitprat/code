#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
using namespace std;

class PalindromicPermutation
{
public:
    static void test()
    {
        PalindromicPermutation obj;
        vector<string> strs = { "abcbcac", "","a", "ab", "aba", "abac", "abdcab" };
        for (auto str : strs) {
            cout << "Is palin : " << str << " : " << obj.IsPalinPerm(str) << endl;
            cout << "Is palin : " << str << " : " << obj.IsPalinPermOptimized(str) << endl;
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
            bitset.set(ch - 'a', !bitset[ch - 'a']);
            if (bitset[ch - 'a']) oddCount++;
            else oddCount--;
        }

        return oddCount <= 1;
    }
};