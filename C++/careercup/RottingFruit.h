#pragma once
#include "../header.h"

class RottingFruit {
   public:
    static void test() {
        RottingFruit obj;

        vector<vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

        auto res = obj.rottingFruit(grid);

        println("Rotting fruit {}", res);
    }

   public:
    int rottingFruit(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();

        int freshFruits = 0;
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) q.push({i, j});      // rotten fruit
                else if (grid[i][j] == 1) freshFruits++;  // fresh fruit
            }
        }

        int minutesRequired = 0;
        while (freshFruits > 0 && !q.empty()) {
            int size = q.size();
            while (size--) {
                auto [r, c] = q.front();
                q.pop();

                for (auto& [nr, nc] : getNeighbours(grid, r, c, n, m)) {
                    q.push({nr, nc});
                    grid[nr][nc] = 2;
                    freshFruits--;
                }
            }

            minutesRequired++;
        }

        return freshFruits == 0 ? minutesRequired : -1;
    }

   public:
    vector<pair<int, int>> getNeighbours(vector<vector<int>>& grid, int r, int c, int n, int m) {
        vector<pair<int, int>> result;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) != abs(j)) {
                    int nr = r + i;
                    int nc = c + j;

                    if (nr < 0 || nc < 0 || nr >= n || nc >= m || grid[nr][nc] != 1) continue;

                    result.push_back({nr, nc});
                }
            }
        }

        return result;
    }
};