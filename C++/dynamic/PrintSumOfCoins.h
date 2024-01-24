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

class PrintSumOfCoins
{
public:
    static void test()
    {
        vector<int> N = { 0,10,15,17,20,50, 100, 1000 };
        vector<int> coins = { 10,15,20 };
        PrintSumOfCoins obj;
        for (auto i : N) {
            cout << i << " = " << obj.makeAllSum(i, coins) << endl;
        }
    }

    string print(int N, vector<int> coins)
    {
        stringstream out;
        unordered_set<int> table;
        table.insert(0);
        for (int sum = 1; sum <= N; sum++) {
            for (auto cointValue : coins) {
                // we can make this sum using this coin value and existing sum
                if (table.find(sum - cointValue) != table.end()) {
                    table.insert(sum);
                    out << sum << ", ";
                }
            }
        }
        out.seekg(-2);

        return out.str();
    }

    string makeAllSum(int N, vector<int> coins)
    {
        stringstream ss;
        for (int i = 1; i <= N; i++)
        {
            if (makeSum(i, coins)) ss << i << ", ";
        }
        ss.seekg(-2);

        return ss.str();
    }

    bool makeSum(int N, vector<int> coins)
    {
        if (N < 0) return false;
        if (N == 0) return true;
        for (auto cur : coins) {
            if (makeSum(N - cur, coins)) return true;
        }

        return false;
    }
};