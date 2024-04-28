#pragma once
#include "../header.h"

class MinCostPath {
    using Matrix = vector<vector<int>>;

   public:
    static void test() {
        MinCostPath obj;
        vector<Matrix> contexts = {
            {{1, 2, 3},
             {4, 8, 2},
             {1, 5, 3}}};
        for (auto context : contexts) {
            auto res = obj.minCostDP(context, {0, 0}, {2, 2});
            cout << "Result:" << res << endl;
        }
    }

   public:
    int minCostRecur1(Matrix mat, Point s, Point d) {
        if (s.x < 0 || s.y < 0 || s.x >= mat.size() || s.y >= mat[0].size()) return 999;
        if (s.x == d.x && s.y == d.y) return mat[d.x][d.y];

        return mat[s.x][s.y] + min(
                                   min(minCostRecur1(mat, {s.x + 1, s.y}, d),
                                       minCostRecur1(mat, {s.x, s.y + 1}, d)),
                                   minCostRecur1(mat, {s.x + 1, s.y + 1}, d));
    }

   public:
    int minCostRecur2(Matrix mat, Point s) {
        if (s.x < 0 || s.y < 0) return INT_MAX;
        if (s.x == 0 && s.y == 0) return mat[s.x][s.y];

        int mn = min(min(minCostRecur2(mat, {s.x + 1, s.y}), minCostRecur2(mat, {s.x, s.y + 1})), minCostRecur2(mat, {s.x + 1, s.y + 1}));

        return mat[s.x][s.y] + mn;
    }

   public:
    int minCostDP(Matrix mat, Point s, Point d) {
        int n = d.x;
        int m = d.y;
        int** table = new int*[n + 1];
        for (int i = 0; i <= n; i++) table[i] = new int[m + 1];

        for (int i = s.x; i <= n; i++) {
            for (int j = s.y; j <= m; j++) {
                if (i == s.x && j == s.y)
                    table[i][j] = mat[i][j];
                else if (i == s.x)
                    table[i][j] = mat[i][j] + table[i][j - 1];
                else if (j == s.y)
                    table[i][j] = mat[i][j] + table[i - 1][j];
                else
                    table[i][j] = mat[i][j] + min(min(table[i - 1][j], table[i][j - 1]), table[i - 1][j - 1]);
            }
        }

        return table[n][m];
    }
};