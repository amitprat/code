#include "../header.h"

class RobotInGrid {
   public:
    static void test() {
        // Define grid dimensions
        const int ROWS = 5;
        const int COLS = 5;

        // cells marked with 1 are blocked
        vector<vector<int>> grid = {
            {0, 0, 0, 0, 0},
            {1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 1},
            {0, 0, 0, 0, 0}};

        RobotInGrid obj;
        Point startPos{0, 0};

        {
            vector<Point> path;
            unordered_set<int> failedPaths;
            bool found = obj.findPathUsingMemoization(grid, grid.size(), grid[0].size(), startPos, {}, failedPaths, path);
            if (found) {
                cout << "Found a path: ";
                for (auto& p : path) cout << p.to_string() << ", ";
                cout << endl;
            }
        }

        {
            vector<vector<Point>> paths;
            bool found = obj.findAllPaths(grid, grid.size(), grid[0].size(), startPos, {}, paths);
            if (found) {
                cout << "Found following paths: " << endl;
                for (auto& path : paths) {
                    for (auto& p : path) cout << p.to_string() << ", ";
                    cout << endl;
                }
                cout << endl;
            }
        }

        {
            bool found = obj.checkIfPathExists(grid, grid.size(), grid[0].size(), startPos);
            cout << "Found following paths: " << found << endl;
        }
    }

    bool findPath(vector<vector<int>>& grid, int n, int m, Point startPos, vector<Point> curPath, vector<Point>& path) {
        if (startPos.x < 0 || startPos.y < 0 || startPos.x >= n || startPos.y >= m) return false;
        if (grid[startPos.x][startPos.y]) return false;  // marked blocked or seen in this recursion path

        if (startPos.x == n - 1 && startPos.y == m - 1) {
            path = curPath;
            return true;
        }

        grid[startPos.x][startPos.y] = 1;
        curPath.push_back(startPos);

        if (findPath(grid, n, m, {startPos.x + 1, startPos.y}, curPath, path) || findPath(grid, n, m, {startPos.x, startPos.y + 1}, curPath, path)) {
            grid[startPos.x][startPos.y] = 0;
            return true;
        }

        grid[startPos.x][startPos.y] = 0;
        curPath.pop_back();

        return false;
    }

    bool findPathUsingMemoization(vector<vector<int>>& grid, int n, int m, Point startPos, vector<Point> curPath, unordered_set<int>& failedPaths, vector<Point>& path) {
        if (startPos.x < 0 || startPos.y < 0 || startPos.x >= n || startPos.y >= m) return false;
        if (grid[startPos.x][startPos.y]) return false;  // marked blocked or seen in this recursion path

        if (startPos.x == n - 1 && startPos.y == m - 1) {
            curPath.push_back(startPos);
            path = curPath;
            return true;
        }

        if (failedPaths.find(startPos.x * m + startPos.y) != failedPaths.end()) {
            return false;
        }

        grid[startPos.x][startPos.y] = 1;
        curPath.push_back(startPos);

        if (findPathUsingMemoization(grid, n, m, {startPos.x + 1, startPos.y}, curPath, failedPaths, path) ||
            findPathUsingMemoization(grid, n, m, {startPos.x, startPos.y + 1}, curPath, failedPaths, path)) {
            grid[startPos.x][startPos.y] = 0;
            return true;
        }

        grid[startPos.x][startPos.y] = 0;

        failedPaths.insert(startPos.x * m + startPos.y);

        return false;
    }

    bool checkIfPathExists(vector<vector<int>>& grid, int n, int m, Point startPos) {
        if (m <= 0 || n <= 0) return false;

        vector<vector<int>> memo(n, vector<int>(m, 0));
        memo[0][0] = grid[0][0] ? 0 : 1;
        for (int j = 1; j < m; j++) {
            memo[0][j] = grid[0][j] ? 0 : memo[0][j - 1];
        }
        for (int i = 1; i < n; i++) {
            memo[i][0] = grid[i][0] ? 0 : memo[i - 1][0];
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (grid[i][j])
                    memo[i][j] = 0;
                else {
                    memo[i][j] = memo[i - 1][j] || memo[i][j - 1];
                }
            }
        }

        bool found = memo[n - 1][m - 1];

        if (found) {
            Point endPos = {n - 1, m - 1};
            while (endPos != startPos) {
                cout << endPos.to_string() << "->";
                if (memo[endPos.x - 1][endPos.y])
                    endPos = Point{endPos.x - 1, endPos.y};
                else if (memo[endPos.x][endPos.y - 1])
                    endPos = Point{endPos.x, endPos.y - 1};
                else {
                    cout << "Invalid";
                    break;
                }
            }
            cout << endl;
        }

        return found;
    }

    bool findAllPaths(vector<vector<int>>& grid, int n, int m, Point startPos, vector<Point> curPath, vector<vector<Point>>& paths) {
        if (startPos.x < 0 || startPos.y < 0 || startPos.x >= n || startPos.y >= m) return false;
        if (grid[startPos.x][startPos.y]) return false;  // marked blocked or seen in this recursion path

        if (startPos.x == n - 1 && startPos.y == m - 1) {
            paths.push_back(curPath);
            return true;
        }

        grid[startPos.x][startPos.y] = 1;
        curPath.push_back(startPos);

        if (findAllPaths(grid, n, m, {startPos.x + 1, startPos.y}, curPath, paths) || findAllPaths(grid, n, m, {startPos.x, startPos.y + 1}, curPath, paths)) {
            grid[startPos.x][startPos.y] = 0;
            return true;
        }

        grid[startPos.x][startPos.y] = 0;

        return false;
    }

    // friend ostream& operator<<(ostream& out, const vector<Point>& path) {
    //     for (auto& p : path) {
    //         out << "{" << p.x << "," << p.y << "}";
    //     }

    //     return out;
    // }
};