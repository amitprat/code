#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class CheckPeriodicString
{
public:
    static void test(vector<string> strs) {
        CheckPeriodicString obj;
        for (auto str : strs) {
            cout << "string: " << str << endl;
            cout << " isPeriodic: " << obj.isPeriodic(str) << endl;
            cout << "Period: " << obj.findPeriod(str) << endl;
        }
    }
    bool isPeriodic(string str)
    {
        string res = str.substr(1) + str.substr(0, str.length() - 2);
        return res.find(str) != string::npos;
    }

    string findPeriod(string str) {
        for (int i = 1; i <= str.length(); i++) {
            if (str.length() % i == 0) {
                string period = str.substr(0, i);
                int j = i;
                while (j + i <= str.length()) {
                    string match = str.substr(j, i);
                    if (period != match) break;
                    j += i;
                }
                if (j == str.length()) return period;
            }
        }

        return "";
    }
};