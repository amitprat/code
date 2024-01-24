#pragma once
#include "../Header.h"

class UniquePaths {
public:
    static void test() {
        UniquePaths obj;
        vector<vector<int>> input = {
            {1, 0, 0, 0} ,
            {0, 0, 0, 0},
            {0, 0, 0, 2}
        };
        cout << obj.uniquePathsIII(input);
    }

    int uniquePathsIII(vector<vector<int>>& grid) {
        pair<int, int> start = getPoint(grid, 1);
        int zeroCnt = getCount(grid, 0);
        unordered_set<string> visited;
        vector<pair<int, int>> path;

        return doDfs(grid, start, visited, path, zeroCnt);
    }

    int doBFS(vector<vector<int>>& grid,
        pair<int, int> cur,
        pair<int, int> end,
        unordered_set<string>& visited) {

        queue<pair<int, int>> q;
        q.push(cur);
        visited.insert(to_string(cur));
        int res = 0;
        while (!q.empty()) {
            cur = q.front(); q.pop();
            if (grid[cur.first][cur.second] == -1) continue;
            if (cur.first == end.first && cur.second == end.second) {
                res += 1;
                continue;
            }
            auto neighbours = getNeighbours(grid, cur, visited);
            for (auto n : neighbours) {
                visited.insert(to_string(n));
                q.push(n);
            }
        }
        return res;
    }

    int doDfs(vector<vector<int>>& grid,
        pair<int, int> cur,
        unordered_set<string>& visited,
        vector<pair<int, int>> path,
        int zeroCnt)
    {
        path.push_back(cur);
        if (grid[cur.first][cur.second] == -1) return 0;
        if (grid[cur.first][cur.second] == 2) {
            if (zeroCnt == -1)
            {
                cout << to_string(path) << endl;
                return 1;
            }
            return 0;
        }
        visited.insert(to_string(cur));

        int res = 0;
        vector<pair<int, int>> neighbours = getNeighbours(grid, cur, visited);
        for (auto& n : neighbours) {
            res += doDfs(grid, n, visited, path, zeroCnt - 1);
        }

        visited.erase(to_string(cur));
        return res;
    }

    vector<pair<int, int>> getNeighbours(vector<vector<int>>& grid,
        pair<int, int> cur,
        unordered_set<string>& visited)
    {
        vector<pair<int, int>> result;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                pair<int, int> newPoint = { cur.first + i,cur.second + j };
                if (abs(i) != abs(j) &&
                    newPoint.first >= 0 &&
                    newPoint.second >= 0 &&
                    newPoint.first < grid.size() &&
                    newPoint.second < grid[0].size()) {
                    if (visited.find(to_string(newPoint)) == visited.end()) {
                        result.push_back(newPoint);
                    }
                }
            }
        }
        return result;
    }

    template <typename T>
    string to_string(pair<T, T> p) {
        return "{" + std::to_string(p.first) + "," + std::to_string(p.second) + "}";
    }

    template <typename T>
    string to_string(vector<pair<T, T>> arr) {
        stringstream ss;
        ss << "[";
        for (auto p : arr) {
            ss << to_string<int>(p) << ", ";
        }
        ss << "]";
        return ss.str();
    }

    pair<int, int> getPoint(vector<vector<int>>& grid, int num) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == num) return { i,j };
            }
        }
        return { -1,-1 };
    }

    int getCount(vector<vector<int>>& grid, int num) {
        int cnt = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == 0) cnt++;
            }
        }
        return cnt;
    }
};