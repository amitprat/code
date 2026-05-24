#pragma once
#include "../header.h"

//
// https://neetcode.io/problems/islands-and-treasure/solution
// You are given a m×n 2D grid initialized with these three possible values:

// -1 - A water cell that can not be traversed.
// 0 - A treasure chest.
// INF - A land cell that can be traversed. We use the integer 2^31 - 1 = 2147483647 to represent INF.
// Fill each land cell with the distance to its nearest treasure chest. If a land cell cannot reach a treasure chest then the value should remain INF.

// Assume the grid can only be traversed up, down, left, or right.

class IslandAndTreasure {
   public:
    static void test() {
        vector<vector<int>> grid = {
            {2147483647, -1, 0, 2147483647},
            {2147483647, 2147483647, 2147483647, -1},
            {2147483647, -1, 2147483647, -1},
            {0, -1, 2147483647, 2147483647}};

        IslandAndTreasure obj;
        obj.getMaxTreasureUsingAllDirectionalBFS(grid);

        for (auto& row : grid) {
            for (auto& val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }

   public:
    void getMaxTreasureUsingDFS(vector<vector<int>>& grid) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == INT_MAX) {  // Only start DFS from land cells
                    unordered_set<int> visited;
                    grid[i][j] = dfs(grid, i, j, visited);
                }
            }
        }
    }

    int dfs(vector<vector<int>>& grid, int x, int y, unordered_set<int>& visited) {
        if (grid[x][y] == 0) return 0;

        visited.insert(x * grid[0].size() + y);  // Mark the current cell as visited

        int dist = INT_MAX;
        for (auto& [nr, nc] : getNeighbors(grid, x, y, visited)) {
            int d = dfs(grid, nr, nc, visited);
            dist = min(dist, d == INT_MAX ? d : 1 + d);
        }

        return dist;
    }

    vector<pair<int, int>> getNeighbors(vector<vector<int>>& grid, int x, int y, unordered_set<int>& visited) {
        vector<pair<int, int>> result;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) != abs(j)) {
                    int nr = x + i;
                    int nc = y + j;
                    if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[nr].size() || grid[nr][nc] == -1 || visited.contains(nr * grid[0].size() + nc)) continue;

                    result.push_back({nr, nc});
                }
            }
        }

        return result;
    }

   public:
    void getMaxTreasureUsingBFS(vector<vector<int>>& grid) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == INT_MAX) {  // Only start DFS from land cells
                    grid[i][j] = bfs(grid, i, j);
                }
            }
        }
    }

    int bfs(vector<vector<int>>& grid, int x, int y) {
        int n = grid.size();
        unordered_set<int> visited;
        queue<pair<int, int>> q;
        q.push({x, y});
        visited.insert(n * x + y);

        int dist = 0;
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [r, c] = q.front();
                q.pop();

                if (grid[r][c] == 0) return dist;

                for (auto& [nr, nc] : getNeighbors(grid, r, c, visited)) {
                    q.push({nr, nc});
                    visited.insert(n * nr + nc);
                }
            }
            dist++;
        }

        return INT_MAX;
    }

   public:
    void getMaxTreasureUsingAllDirectionalBFS(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                if (grid[i][j] == 0) {  // Start from treasure cells
                    q.push({i, j});
                }
            }
        }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (auto& [nr, nc] : getNeighbors(grid, r, c)) {
                q.push({nr, nc});
                grid[nr][nc] = 1 + grid[r][c];
            }
        }
    }

    vector<pair<int, int>> getNeighbors(vector<vector<int>>& grid, int x, int y) {
        vector<pair<int, int>> result;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (abs(i) != abs(j)) {
                    int nr = x + i;
                    int nc = y + j;
                    if (nr < 0 || nc < 0 || nr >= grid.size() || nc >= grid[nr].size() || grid[nr][nc] != INT_MAX) continue;

                    result.push_back({nr, nc});
                }
            }
        }

        return result;
    }
};