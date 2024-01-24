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

class FindAnagrams
{
public:
    static void test(vector<string> strs)
    {
        FindAnagrams obj;
        auto res = obj.calculate(strs);
        for (auto r : res) {
            cout << r.first << " : ";
            for (auto s : r.second) {
                cout << s << " ";
            }
            cout << endl;
        }
    }

    vector <pair<unsigned long long, vector<string>>> calculate(vector<string> str)
    {
        vector <pair<unsigned long long, vector<string>>> res;
        for (auto s : str) {
            unsigned long long h = hash(s);
            bool exist = false;
            for (auto& v : res) {
                if (v.first == h) {
                    v.second.push_back(s);
                    exist = true;
                }
            }
            if (!exist) res.push_back({ h, {s} });
        }

        return res;
    }

    unsigned long long hash(string str) {
        int radix = 256;
        int pw = 10;
        unsigned long long res = 0;
        for (auto ch : str) {
            res += pow(radix, pw) + ch;
            pw++;
        }

        return res;
    }
};