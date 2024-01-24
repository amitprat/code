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
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class CompressString
{
public:
    static void test()
    {
        CompressString obj;
        vector<string> str = { "","a","abc","aabc","abbc","abcc","aaaaaaa","aabbbccc" };
        for (auto s : str) {
            auto res = obj.compress(s);
            cout << "String: " << s << " : " << res << endl;
        }
    }

    string compress(string str)
    {
        if (str.size() == 0) return str;

        int i = 1, j = 1;
        char prev = str[0];
        int cnt = 1;
        while (i < str.size()) {
            if (str[i] == prev) cnt++;
            else {
                if (cnt > 1) str[j++] = cnt + '0';
                prev = str[j++] = str[i];
                cnt = 1;
            }
            i++;
        }
        if (cnt > 1) str[j++] = cnt + '0';

        return str.substr(0, j);
    }
};