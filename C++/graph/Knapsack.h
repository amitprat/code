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
using Container = vector<int>;
using KNAPSACK = tuple< Container, Container, int>;

class Knapsack
{
public:
    static void test()
    {
        Knapsack obj;
        vector <KNAPSACK> contexts =
        {
            {{60, 100, 120} ,{10, 20, 30},50}
        };
        for (auto context : contexts)
        {
            auto res = obj.knapsackDP(get<0>(context), get<1>(context), get<2>(context));
            cout << "Result:" << res << endl;
        }
    }

    int knapsack(Container profits, Container weights, int capacity)
    {
        int mx = 0;
        int tmpMax = 0;
        vector<int> mxItems;
        vector<int> tmpItems;
        int n = mxItems.size();
        knapsackUtil(profits, weights, capacity, profits.size() - 1, tmpMax, tmpItems, mx, mxItems);
        for (auto i : mxItems) cout << i << " ";
        cout << endl;

        return mx;
    }

    int knapsackDP(Container profits, Container weights, int capacity)
    {
        int n = profits.size();
        int** table = new int* [n + 1];
        for (int i = 0; i <= n; i++) table[i] = new int[capacity + 1];

        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= capacity; j++)
            {
                if (i == 0 || j == 0) table[i][j] = 0;
                else {
                    if (weights[i - 1] <= j) table[i][j] = max(table[i - 1][j - weights[i - 1]] + profits[i - 1], table[i - 1][j]);
                    else table[i][j] = table[i - 1][j];
                }
            }
        }

        return table[n][capacity];
    }

private:
    void knapsackUtil(Container profits, Container weights, int capacity, int n, int tmpMax, vector<int>& tmpItems, int& mx, vector<int>& items)
    {
        if (capacity < 0) return;
        if (tmpMax > mx) {
            mx = tmpMax;
            items = tmpItems;
        }
        if (n < 0) return;

        knapsackUtil(profits, weights, capacity, n - 1, tmpMax, tmpItems, mx, items);
        tmpItems.push_back(profits[n]);
        knapsackUtil(profits, weights, capacity - weights[n], n - 1, tmpMax + profits[n], tmpItems, mx, items);
        tmpItems.pop_back();
    }
};