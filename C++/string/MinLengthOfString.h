#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <tuple>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class MinLengthOfString
{
public:
    static void test()
    {
        MinLengthOfString obj;
        string  s = "abbcbcba";
        unordered_set<char> set = { 'a','b','c' };
        pair<int, int> mnLen = obj.findMinLen(s, set);
        cout << mnLen.first << " " << mnLen.second << endl;
    }

    pair<int, int> findMinLen(string str, unordered_set<char> set)
    {
        pair<int, int> cnt = { INT_MAX, INT_MAX };
        int count = 0;
        int start = 0;
        unordered_map<char, int> map;
        for (int i = 0; i < str.size(); i++)
        {
            map[str[i]]++;
            if (map[str[i]] == 1) count++;
            while (count == set.size()) {
                map[str[start]]--;
                if (set.find(str[start]) != set.end() && map[str[start]] == 0) count--;
                if (i - start + 1 < cnt.second) {
                    cnt = { start, i - start + 1 };
                }
                start++;
            }
        }

        return cnt;
    }
};