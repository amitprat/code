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
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class FindSameCountSubstr
{
public:
    static void test()
    {
        FindSameCountSubstr obj;
        vector<string> strs = { "", "a", "1", "11", "aa", "1a1", "a11a", "1aa1", "a111a", "1asd1s", "asdasd12312131a","1a1" };
        for (auto str : strs) {
            auto res = obj.find1(str);
            cout << str << " = " << res << endl;
        }
    }

    string find1(string str)
    {
        unordered_map<int, int> map;
        pair<int, int> res = { 0,-1 };
        int diff = 0;
        map[diff] = 0;
        for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i])) diff++;
            else if (isalpha(str[i])) diff--;
            if (map.find(diff) == map.end()) {
                map[diff] = i + 1;
            }
            else {
                auto s = map[diff];
                if (i - s + 1 > res.second) {
                    res = { s, i - s + 1 };
                }
                cout << s << " " << i << endl;
            }
        }

        return str.substr(res.first, res.second);
    }

    string find(string str)
    {
        int mx = 0;
        pair<int, int> res;
        for (int j = str.length() - 1; j >= 1; j--) {
            for (int i = 0; i < j; i++) {
                if (equal(str, i, j) && j - i + 1 > mx) { mx = j - i + 1; res = { i,j }; }
            }
        }

        if (mx > 0) return str.substr(res.first, res.second - res.first + 1);
        return string();
    }

    bool equal(string str, int s, int e) {
        int cnt = 0;
        for (int i = s; i <= e; i++) {
            if (str[i] >= '0' && str[i] <= '9') cnt++;
            else cnt--;
        }

        return cnt == 0;
    }
};