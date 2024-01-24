#pragma once
#include <time.h>
#include <stdlib.h>
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
using namespace std;
using ROD = pair<vector<int>, vector<int>>;

class CutRod
{
public:
    static void test()
    {
        CutRod obj;
        vector<ROD> contexts =
        {
            {{1,2,3,4,5,6,7,8},{1,5,8,9,10,17,17,20}} ,
            {{1,2,3,4,5,6,7,8},{3,5,8,9,10,17,17,20}}
        };
        for (auto context : contexts)
        {
            cout << "Input:";
            for (auto j : context.second) cout << j << " ";
            cout << endl;
            int l = context.first.size() > 0 ? context.first[context.first.size() - 1] : 0;
            auto res = obj.cutRodDP(context.first, context.second, 0, context.first.size() - 1, 0, l);
            cout << "Result:" << res << endl;
        }
    }

    int cutRod(vector<int> l, vector<int> p, int s, int e, int c, int m)
    {
        if (e < s) return 0;
        if (s == e && c + l[s] <= m) return p[0];
        int without = cutRod(l, p, s + 1, e, c, m);
        int with = 0;
        if (c + l[s] <= m) with = p[s] + cutRod(l, p, s, e, c + l[s], m);
        return max(with, without);
    }

    int cutRodDP(vector<int> l, vector<int> p, int s, int e, int c, int m)
    {
        int n = e - s + 1;
        int* table = new int[m + 1];
        for (int i = 0; i <= m; i++) table[i] = 0;

        for (int len = 1; len <= m; len++) {
            for (int index = 1; index <= n; index++) {
                if (len >= l[index - 1])table[len] = max(table[len], p[index - 1] + table[len - l[index - 1]]);
                else table[len] = max(table[len], table[len - 1]);
            }
        }
        print(table, n);

        return table[n];
    }

    void print(int* table, int n) {
        cout << "-------------------------" << endl;
        for (int i = 0; i <= n; i++) {
            cout << table[i] << " ";
        }
        cout << "\n-------------------------" << endl << endl;
    }
};