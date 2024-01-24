#pragma once
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <cassert>
#include <fstream>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <string>
#include <sstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <cassert>
using namespace std;

class BinomialCoeff
{
public:
    static void test()
    {
        BinomialCoeff obj;
        vector<pair<int, int>> tests = {
            {0,0},
            {1,1},
            {2,1},
            {5,2},
            {10,0}
        };

        for (auto test : tests) {
            cout << "Coefficient: " << test.first << ", " << test.second << " = ";
            auto res = obj.binomialCoeff(test.first, test.second);
            cout << res << endl;
            assert(res == obj.binomialCoeff2(test.first, test.second));
        }
    }

    int binomialCoeff(int c, int r)
    {
        if (c == r || r == 0) return 1;
        return binomialCoeff(c - 1, r - 1) + binomialCoeff(c - 1, r);
    }

    int binomialCoeff2(int c, int r)
    {
        r = min(r, c - r);
        int res = 1;
        for (int i = 0; i < r; i++) {
            res *= (c - i);
            res /= (i + 1);
        }

        return res;
    }
};