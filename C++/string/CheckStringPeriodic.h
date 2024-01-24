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

class CheckStringPeriodic
{
private:
public:
    static void test(vector<string> inputs)
    {
        CheckStringPeriodic obj;
        for (auto input : inputs) {
            auto res = obj.findPeriod(input);
            cout << "String: " << input << ", Periodic: " << res << endl;
        }
    }

    bool isPeriodic(string input) {
        string tmp = input + input;
        tmp.pop_back();
        return tmp.find(input, 1);
    }

    string findPeriod(string input)
    {
        string res;
        for (int i = 1; i <= input.size() / 2; i++) {
            string tmp = input.substr(0, i);
        }
        return res;
    }
};