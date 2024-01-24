#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <unordered_set>
using namespace std;

class SpecialEquivalentStrings
{
public:
    static void test(vector<string> strs)
    {
        SpecialEquivalentStrings obj;
        cout << "Result: " << obj.calculate(strs) << endl;
    }

    int calculate(vector<string> strs)
    {
        unordered_map<int, vector<string>> m;
        for (auto str : strs) {
            int h = hash(str);
            m[h].push_back(str);
        }
        cout << "Map::" << endl;
        for (auto i : m) {
            cout << i.first << ":{";
            for (auto j : i.second) cout << j << " ";
            cout << "}";
        }
        cout << endl;
        return m.size();
    }

    int hash(string str)
    {
        int h = 0;
        int eh = 0;
        int oh = 0;
        for (int i = 0; i < str.size(); i++) {
            if (i & 1) {
                eh += str[i];
            }
            else {
                oh += str[i];
            }
        }

        h = 256 * eh + oh;

        return h;
    }
};