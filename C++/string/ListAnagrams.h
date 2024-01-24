#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;

class ListAnagrams
{
public:
    static void test(vector<string> v)
    {
        ListAnagrams obj;
        cout << "Input: ";
        for (auto i : v) cout << i << " ";
        cout << "Output: ";
        auto res = obj.listAnagrams(v);
        for (auto i : res) {
            cout << "[";
            for (auto j : i.second) cout << j << " ";
            cout << "] ";
        }
        cout << endl;
    }

    unordered_map<string, list<string>> listAnagrams(vector<string>& v)
    {
        unordered_map<string, list<string>> res;
        for (auto i : v) {
            auto s = i;
            sort(s.begin(), s.end());
            res[s].push_back(i);
        }
        return res;
    }
};