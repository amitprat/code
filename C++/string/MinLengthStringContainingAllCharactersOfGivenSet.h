#pragma once
#include "../Header.h"
using namespace std;

class MinLengthStringContainingAllCharactersOfGivenSet
{
public:
    static void test()
    {
        MinLengthStringContainingAllCharactersOfGivenSet obj;
        string  s = "abbcbcba";
        unordered_set<char> set = { 'a','b','c' };
        auto mnLenStr = obj.findMinLen(s, set);

        cout << format("Minimum length substring of={} which contains all characters of={} is={}", s, to_string(set), mnLenStr) << endl;
    }

    string findMinLen(string str, unordered_set<char> set)
    {
        pair<int, int> result = { INT_MAX, INT_MAX };
        int count = 0;
        int start = 0;
        vector<int> freq(256, 0);

        for (int i = 0; i < str.size(); i++)
        {
            if (freq[str[i]] == 0) count++;
            freq[str[i]]++;

            while (count > set.size()) {
                freq[str[start]]--;
                if (freq[str[start]] == 0) count--;

                start++;
            }

            if (count == set.size() && i - start + 1 < result.second) {
                result = { start, i - start + 1 };
            }
        }

        if (result.first == INT_MAX) return string();
        return str.substr(result.first, result.second);
    }
};