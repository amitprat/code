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

class SimpleExprEval
{
public:
    static void test(vector<string> expressions)
    {
        SimpleExprEval obj;
        for (auto expr : expressions)
        {
            cout << "Expression: " << expr << ", ";
            cout << "Result: " << obj.evaluate(expr) << endl;
        }
    }

    int evaluate(string expr)
    {
        vector<string> additives = tokenize(expr, '+');
        int res = 0;
        for (auto i : additives)
        {
            vector<string> multiplicatives = tokenize(i, '*');
            int mul = 1;
            for (auto j : multiplicatives)
            {
                mul *= stoi(j);
            }
            res += mul;
        }

        return res;
    }

    vector<string> tokenize(string str, char ch)
    {
        vector<string> res;

        int start = 0;
        size_t pos = str.find(ch, start);
        while (pos != string::npos)
        {
            res.push_back(str.substr(start, pos - start));
            start = pos + 1;
            pos = str.find(ch, start);
        }
        if (start != str.length())
            res.push_back(str.substr(start));

        return res;
    }
};