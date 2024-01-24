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
#include <sstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class MutationsOfString
{
public:
    static void test()
    {
        MutationsOfString obj;
        string str = "fab";
        unordered_map<char, vector<char>> m = {
            {'f', {'F', '4'}},
            {'b', {'B', '8'}}
        };

        obj.generate(str, m, str.size());
    }

    void generate(string str, unordered_map<char, vector<char>> m, int n)
    {
        if (n == 0) { cout << str << " "; return; }
        generate(str, m, n - 1);
        if (m.find(str[n - 1]) != m.end()) {
            vector<char> elems = m[str[n - 1]];
            for (auto e : elems) {
                str[n - 1] = e;
                generate(str, m, n - 1);
            }
        }
    }
};