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

class KMP
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
            auto res = substringSearch(i.first, i.second);
            cout << "Found at indices = {";
            for (auto j : res.first) cout << j << " ";
            cout << "}" << endl;
        }
    }

    pair<vector<int>, int> substringSearch(string txt, string pat)
    {
        int m = pat.length();
        int n = txt.length();

        vector<int> lps = calculateLPS(pat, m);
        cout << "lps: {";
        for (auto i : lps) cout << i << " ";
        cout << "}, ";

        vector<int> indices;
        int count = 0;
        int i = 0, prefixMatch = 0;
        cout << "prefixmatch: {";
        while (i < n) {
            cout << prefixMatch << " ";
            if (txt[i] == pat[prefixMatch]) i++, prefixMatch++;
            if (prefixMatch == m) {
                indices.push_back(i - prefixMatch);
                count++;
                prefixMatch = lps[prefixMatch - 1];
            }
            else if (i < n && txt[i] != pat[prefixMatch]) {
                if (prefixMatch != 0) prefixMatch = lps[prefixMatch - 1];
                else i++;
            }
        }
        cout << "} :: ";

        return { indices, count };
    }

    vector<int> calculateLPS(string pat, int m)
    {
        vector<int> lps;
        lps.resize(m);
        int len = 0; // longest prefix length so far
        lps[0] = len;

        int i = 1;
        while (i < m) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if (len != 0) len = lps[len - 1];
                else lps[i++] = 0;
            }
        }

        return lps;
    }
};