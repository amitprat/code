#include "../header.h"

class Knapsack {
   private:
    int knapsack(vector<int>& vals, vector<int>& wt, int n, int W) {
        if (n <= 0 || W <= 0) return 0;

        return max(knapsack(vals, wt, n - 1, W), vals[n - 1] + knapsack(vals, wt, n - 1, W - wt[n - 1]));
    }

    int knapsackDP(vector<int>& vals, vector<int>& wt, int n, int W) {
        vector<vector<int>> table(W + 1, vector<int>(n + 1));

        for (int i = 0; i < W; i++) {
            for (int j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else if (wt[j - 1] > i)
                    table[i][j] = table[i][j - 1];
                else
                    table[i][j] = max(table[i][j - 1], vals[j - 1] + table[i - wt[j - 1]][j - 1]);
            }
        }

        return table[W][n];
    }

    int knapsackDP2(vector<int>& vals, vector<int>& wt, int n, int W) {
        vector<int> table(W + 1, 0);

        for (int i = 0; i < n; i++) {
            for (int w = W; w >= wt[i - 1]; w--) {
                table[w] = max(table[w], vals[i] + table[w - wt[i]]);
            }
        }

        return table[W];
    }
};