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
using Matrix = vector<vector<int>>;
using Point = pair<int, int>;

class MinCostPath
{
public:
    static void test()
    {
        MinCostPath obj;
        vector <Matrix> contexts =
        {
            {
                {1, 2, 3},
                {4, 8, 2},
                {1, 5, 3}
            }
        };
        for (auto context : contexts)
        {
            auto res = obj.minCostDP(context, { 0,0 }, { 2, 2 });
            cout << "Result:" << res << endl;
        }
    }

    int minCost(Matrix mat, Point s, Point d)
    {
        if (s.first < 0 || s.second < 0 || s.first >= mat.size() || s.second >= mat[0].size()) return 999;
        if (s.first == d.first && s.second == d.second) return mat[d.first][d.second];

        return mat[s.first][s.second] + min(
            min(minCost(mat, { s.first + 1,s.second }, d),
                minCost(mat, { s.first,s.second + 1 }, d)),
            minCost(mat, { s.first + 1,s.second + 1 }, d)
        );
    }

    int minCostDP(Matrix mat, Point s, Point d)
    {
        int n = d.first;
        int m = d.second;
        int** table = new int* [n + 1];
        for (int i = 0; i <= n; i++) table[i] = new int[m + 1];
        for (int i = s.first; i <= n; i++)
        {
            for (int j = s.second; j <= m; j++)
            {
                if (i == s.first && j == s.second)  table[i][j] = mat[i][j];
                else if (i == s.first) table[i][j] = mat[i][j] + table[i][j - 1];
                else if (j == s.second) table[i][j] = mat[i][j] + table[i - 1][j];
                else table[i][j] = mat[i][j] + min(min(table[i - 1][j], table[i][j - 1]), table[i - 1][j - 1]);
            }
        }

        return table[n][m];
    }
};