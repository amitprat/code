#pragma once

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <time.h>
#include <stack>
#include <tuple>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <fstream>
using namespace std;

class CombinationOfNumbersToGivenSum
{
public:
    static void test()
    {
        CombinationOfNumbersToGivenSum obj;
        vector<vector<int>> res;
        vector<int> tmp;
        int N = 4;
        obj.generate(1, 0, N, tmp, res);

        for (auto i : res) {
            for (auto j : i) cout << j << " ";
            cout << endl;
        }
    }

    void generate(int index, int cur, int N, vector<int> tmp, vector<vector<int>>& res)
    {
        if (cur > N) return;
        if (cur == N) {
            if (!tmp.empty()) res.push_back(tmp);
            return;
        }

        for (int i = index; i <= N; i++)
        {
            tmp.push_back(i);
            generate(i, cur + i, N, tmp, res);
            tmp.pop_back();
        }
    }
};