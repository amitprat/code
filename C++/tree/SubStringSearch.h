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
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

class SubStringSearch
{
public:
    void test()
    {
        vector<pair<string, string>> v = {
            {"abcde", "bcd"},
            {"aaaaaa", "aa"},
            {"abcdefghcde", "cde"}
        };

        for (auto i : v) {
            cout << "Processing: {" << i.first << ", " << i.second << "} : ";
            auto res = substringSearch2(i.first, i.second);
            cout << "Found at indices = {";
            for (auto j : res.first) cout << j << " ";
            cout << "}, repeat count = " << res.second << endl;
        }
    }

    pair<vector<int>, int> substringSearch(string txt, string pat)
    {
        vector<int> indices;
        int count = 0;
        int n = txt.length();
        int m = pat.length();
        for (int i = 0, j = 0; i < n; i++) {
            if (txt[i] == pat[j]) j++;
            else {
                i -= j; j = 0;
            }
            if (j == m) { indices.push_back(i - j + 1); count++; }
        }

        return { indices, count };
    }

    pair<vector<int>, int> substringSearch2(string txt, string pat)
    {
        vector<int> indices;
        int count = 0;
        int n = txt.length();
        int m = pat.length();
        for (int i = 0; i < n - m + 1; i++) {
            int j = 0;
            for (j = 0; j < m && (txt[i + j] == pat[j]); j++);
            if (j == m) { indices.push_back(i); count++; }
        }

        return { indices, count };
    }
};