#pragma once
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
#include <string>
#include <functional>
#include <future>
using namespace std;

class GetPeriod
{
public:
    static void test()
    {
        GetPeriod obj;
        vector<pair<string, string>> strs = {{"ababab", "ab"}, {"xxxxx", "x"}, {"aabbaaabba", "aabba"}};
        for (auto str : strs)
        {
            string p;
            int n;
            bool res = obj.getPeriod(str.first, p, n);
            cout << "str={" << str.first << ", " << str.second << "}"
                 << ", p=" << p << ", n=" << n << endl;
        }
    }

    bool isPeriod(string str)
    {
        string cur = str.substr(1) + str.substr(0, str.length() - 1);
        return cur.find(str) != string::npos;
    }

    bool getPeriod(string str, string &p, int &n)
    {
        int l = str.length();
        for (int i = 1; (i <= l / 2); i++)
        {
            if (l % i == 0)
            {
                p = str.substr(0, i);
                int j = i;
                int cnt = 1;
                while (j + i <= l)
                {
                    cnt++;
                    string cur = str.substr(j, i);
                    if (cur == p)
                        j += i;
                    else
                        break;
                }
                if (j == l)
                {
                    n = cnt;
                    return true;
                }
            }
        }

        return false;
    }
};

// Another solution
bool isPeriod(string str)
{
    string cur = str.substr(1) + str.substr(0, str.length() - 1);
    return cur.find(str) != string::npos;
}

pair<string, int> getPeriod(string str)
{
    int total = str.length();
    int half = total / 2;
    for (int l = 1; l <= half; l++)
    {
        if (total % l == 0)
        {
            string period = str.substr(0, l);
            int j = l;
            while (j + l <= total)
            {
                string next = str.substr(j, l);
                if (next != period)
                    break;
                j += l;
            }
            if (j == total)
                return {period, total / l};
        }
    }
    return {"", 0};
}

int main()
{
    string str = "ababab";
    bool res = isPeriod(str);
    if (res)
    {
        auto val = getPeriod(str);
        cout << val.first << " " << val.second << endl;
    }

    return 0;
}