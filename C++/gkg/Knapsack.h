#pragma once
#include "../Header.h"

class Knapsack {
public:
    static void test() {
        int val[] = { 60, 100, 120 };
        int wt[] = { 10, 20, 30 };
        int W = 50;
        int n = 3;

        int res = maxProfitMemoryOpt(val, wt, W, n);
        cout << "Max profit = " << res << endl;
    }

    static int maxProfitMemoryOpt(int val[], int wt[], int W, int n) {
        int* table = new int[W + 1];
        memset(table, 0, sizeof(table));

        for (int i = 0; i < n; i++) {
            for (int w = W; w >= 0; w--) {
                if (wt[i] <= w) {
                    table[w] = max(table[w], val[i] + table[w - wt[i]]);
                }
            }
        }

        return table[W];
    }

    static int maxProfit(int val[], int wt[], int W, int n) {
        vector<vector<int>> table(W + 1, vector<int>(n + 1, 0));

        for (int w = 0; w <= W; w++) {
            for (int i = 0; i <= n; i++) {
                if (w == 0 || i == 0) table[w][i] = 0;
                else {
                    table[w][i] = table[w][i - 1];
                    if (w >= wt[i - 1]) {
                        table[w][i] = max(table[w][i], val[i - 1] + table[w - wt[i - 1]][i - 1]);
                    }
                }
            }
        }

        return table[W][n];
    }
};