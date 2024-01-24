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

class LongestIncreasingSubsequence
{
public:
    static void test()
    {
        LongestIncreasingSubsequence lis;
        vector < pair<vector<int>, vector<int>>> contexts =
        {
            {{3, 10, 2, 1, 20},{3, 10, 20}},
        {{3,2},{2}},
        {{50, 3, 10, 7, 40, 80},{3, 7, 40, 80} }
        };
        for (auto context : contexts)
        {
            cout << "Input:";
            std::copy(context.first.begin(), context.first.end(), std::ostream_iterator<int>(std::cout, " "));
            cout << endl;
            auto res = lis.findLISDP(context.first);
            cout << "Result:" << res << endl;
            //cout << "Result:";
            //std::copy(res.begin(), res.end(), std::ostream_iterator<int>(std::cout, " "));
            //cout << endl;
            //assert(res.size() == context.second.size());
            //for (int i = 0; i < res.size(); i++) {
            //    assert(res[i] == context.second[i]);
            //}
        }
    }

    vector<int> findLIS(vector<int> in)
    {
        vector<int> res;
        vector<int> tmp;
        findLISUtil(in, INT_MIN, 0, tmp, res);

        return res;
    }

    int findLISDP(vector<int> in)
    {
        /*vector<int> res;*/
        int* table = new int[in.size()];
        table[0] = 1;
        for (int i = 1; i < in.size(); i++)
        {
            table[i] = 1;
            for (int j = i - 1; j >= 0; j--)
            {
                if (in[i] >= in[j])
                {
                    table[i] = max(table[i], 1 + table[j]);
                }
            }
        }
        int maxLis = 1;
        int maxLisIndex = 0;
        for (int i = 0; i < in.size(); i++)
        {
            if (table[i] > maxLis) {
                maxLis = table[i];
                maxLisIndex = i;
            }
        }

        //int curMax = maxLis;
        //int curMaxIndex = maxLisIndex;
        //for (int i = maxLisIndex; i >= 0; i--)
        //{
        //    if (i == curMaxIndex && in[i] <= curMax) {
        //        res.push_back(in[i]);
        //        curMax = in[i];
        //        curMaxIndex--;
        //    }
        //}

        return maxLis;
    }

private:
    void findLISUtil(vector<int> in, int prev, int idx, vector<int> tmp, vector<int>& res)
    {
        if (idx >= in.size()) {
            if (tmp.size() > res.size()) res = tmp;
            return;
        }

        if (in[idx] < prev) findLISUtil(in, prev, idx + 1, tmp, res);
        else {
            findLISUtil(in, prev, idx + 1, tmp, res);
            tmp.push_back(in[idx]);
            findLISUtil(in, in[idx], idx + 1, tmp, res);
        }
    }
};