#pragma once
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <bitset>
#include <string>
#include <functional>
#include <future>
#include "AsyncState.h"
using namespace std;

class CountABCCombination
{
public:
    static void test()
    {
        int b = 1, c = 2;
        int n = 3;
        CountABCCombination obj;
        vector<string> result;
        cout << obj.count(b, c, n, result, "") << endl;
        for (auto s : result) cout << s << " ";
        cout << endl;

        cout << obj.countMemo(b, c, n) << endl;
    }

    int count(int b, int c, int n, vector<string>& result, string cur)
    {
        if (n < 0 || b < 0 || c < 0) return 0;
        if (n == 0) {
            result.push_back(cur);
            return 1;
        }

        int cnt = count(b, c, n - 1, result, cur + "a");
        cnt += count(b - 1, c, n - 1, result, cur + "b");
        cnt += count(b, c - 1, n - 1, result, cur + "c");
        return cnt;
    }

    int countMemo(int b, int c, int n, int table[3][2][3])
    {
        if (b < 0 || c < 0 || n < 0) return 0;
        if (n == 0) {
            table[n][b][c] = 1; return table[n][b][c];
        }
        if (table[n][b][c] != -1) return table[n][b][c];

        int res = countMemo(b, c, n - 1, table) + countMemo(b - 1, c, n - 1, table) + countMemo(b, c - 1, n - 1, table);
        return (table[n][b][c] = res);
    }

    int countMemo(int b, int c, int n)
    {
        int table[3][2][3];
        memset(table, -1, sizeof(table));
        return countMemo(b, c, n, table);
    }
};