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

class IntegerToString
{
public:
    static void test(vector<int> vals)
    {
        IntegerToString obj;
        for (auto val : vals) {
            cout << "Input" << " : " << val << endl;
            auto res = obj.calculate(val);
            cout << "Output" << " : " << res << endl;
        }
    }

    string calculate(int val)
    {
        string res;
        int rem = 0;
        bool isNeg = false;
        if (val < 0) { isNeg = true; val = -1 * val; }
        while (val) {
            rem = val % 10;
            val /= 10;
            res = string(1, rem + '0') + res;
        }
        if (isNeg) res = "-" + res;

        return res;
    }
};