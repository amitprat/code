#pragma once
#include "../header.h"

class Knapsack {
   public:
    static void test() {
        vector<int> vals = {60, 100, 120};
        vector<int> wt = {10, 20, 30};
        int W = 50;
        int n = 3;

        Knapsack obj;
        int res = obj.knapsackDP1DArray(vals, wt, W, n);
        cout << "Max profit = " << res << endl;
    }

   private:
    int knapsackRecur(vector<int>& vals, vector<int>& wt, int n, int W) {
        if (n <= 0 || W <= 0) return 0;

        return max(knapsackRecur(vals, wt, n - 1, W), vals[n - 1] + knapsackRecur(vals, wt, n - 1, W - wt[n - 1]));
    }

   private:
    // get items which are part of knapsack.
    int knapsackRecur_2(vector<int>& vals, vector<int>& wt, int n, int W) {
        vector<int> totalMax;
        knapsackRecurUtil_2(vals, wt, n, W, {}, totalMax);
        cout << totalMax << endl;

        return std::accumulate(totalMax.begin(), totalMax.end(), 0);
    }

    void knapsackRecurUtil_2(vector<int>& vals, vector<int>& wt, int n, int W, vector<int> curMax, vector<int>& totalMax) {
        if (W < 0) return;
        if (n == 0) {
            int sum = std::accumulate(curMax.begin(), curMax.end(), 0);
            int total = std::accumulate(totalMax.begin(), totalMax.end(), 0);
            if (sum > total) {
                totalMax = curMax;
            }
            return;
        }

        knapsackRecurUtil_2(vals, wt, n - 1, W, curMax, totalMax);

        curMax.push_back(vals[n - 1]);
        knapsackRecurUtil_2(vals, wt, n - 1, W, curMax, totalMax);
        curMax.pop_back();
    }

   private:
    int knapsackDP2DArray(vector<int>& vals, vector<int>& wt, int n, int W) {
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

   private:
    int knapsackDP2DArray_2(vector<int>& vals, vector<int>& wt, int n, int W) {
        int n = vals.size();
        int** table = new int*[n + 1];
        for (int i = 0; i <= n; i++) table[i] = new int[W + 1];

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= W; j++) {
                if (i == 0 || j == 0)
                    table[i][j] = 0;
                else {
                    if (wt[i - 1] <= j)
                        table[i][j] = max(table[i - 1][j - wt[i - 1]] + vals[i - 1], table[i - 1][j]);
                    else
                        table[i][j] = table[i - 1][j];
                }
            }
        }

        return table[n][W];
    }

   private:
    int knapsackDP1DArray(vector<int>& vals, vector<int>& wt, int n, int W) {
        vector<int> table(W + 1, 0);

        for (int i = 0; i < n; i++) {
            for (int w = W; w >= wt[i - 1]; w--) {
                table[w] = max(table[w], vals[i] + table[w - wt[i]]);
            }
        }

        return table[W];
    }
};
