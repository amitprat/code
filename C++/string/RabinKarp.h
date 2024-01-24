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

class Hasher
{
private:
    unsigned long q; // large prime number
    unsigned int r; // radix
    int m; // pat length
    unsigned long rm; // R^(M-1) % Q

public:
    Hasher(int m) {
        this->r = 256;
        this->q = 7901;
        this->m = m;

        rm = 1;
        for (int i = 1; i <= m - 1; i++)
            rm = (r * rm) % q;
    }

    unsigned long hash(const string& str)
    {
        int h = 0;
        for (int i = 0; i < m; i++) {
            h = (r * h + str[i]) % q;
        }

        return h;
    }

    unsigned long hash(unsigned long hash, char old, char cur)
    {
        hash = (hash + q - rm * old % q) % q;
        hash = (hash * r + cur) % q;

        return hash;
    }
};

class RabinKarp
{
private:
    Hasher* hasher;

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
            cout << "}, repeat count = " << res.second << endl;
        }
    }

    pair<vector<int>, int> substringSearch(string txt, string pat)
    {
        int m = pat.length();
        int n = txt.length();
        hasher = new Hasher(m);
        unsigned long txtHash = hasher->hash(txt);
        unsigned long patHash = hasher->hash(pat);

        vector<int> indices;
        int count = 0;

        for (int i = m; i <= n; i++) {
            if (txtHash == patHash) {
                indices.push_back(i - m);
                count++;
            }
            if (i < n) txtHash = hasher->hash(txtHash, txt[i - m], txt[i]);
        }

        return { indices, count };
    }
};