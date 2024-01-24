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

class EditDistance
{
private:
    int EDIT_COST = 1;
    int DELETE_COST = 1;
    int INSERT_COST = 1;

public:
    static void test()
    {
        EditDistance obj;
        vector < pair<string, string>> contexts =
        { {"geek","gesek"},
        {"cat","cut"},
        {"sunday","saturday"}
        };
        for (auto context : contexts)
        {
            cout << "Input:" << context.first << ", " << context.second << endl;
            auto res = obj.editDistanceDP(context.first, context.second, context.first.size(), context.second.size());
            cout << "Result:" << res << endl;
        }
    }

    int editDistance(string f, string s, int n, int m)
    {
        if (n == 0 && m == 0) return 0;
        if (n <= 0 || m <= 0) {
            if (n <= 0) return m;
            else return n;
        }

        if (f[n - 1] == s[m - 1]) return editDistance(f, s, n - 1, m - 1);
        return min(min(DELETE_COST + editDistance(f, s, n - 1, m), INSERT_COST + editDistance(f, s, n, m - 1)), EDIT_COST + editDistance(f, s, n - 1, m - 1));
    }

    int editDistanceDP(string f, string s, int n, int m)
    {
        int** table = new int* [n + 1];
        for (int i = 0; i <= n; i++) table[i] = new int[m + 1];
        for (int i = 0; i <= n; i++) table[i][0] = i;
        for (int i = 0; i <= m; i++) table[0][i] = i;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (f[i - 1] == s[j - 1]) table[i][j] = table[i - 1][j - 1];
                else {
                    table[i][j] = min(min(INSERT_COST + table[i - 1][j], DELETE_COST + table[i][j - 1]), EDIT_COST + table[i - 1][j - 1]);
                }
            }
        }

        return table[n][m];
    }
};