#pragma once
#include "../header.h"

// Note - DP isn't correct approach for this problem as we need to calculate area of connected 1s, so we need to
// do DFS/BFS/UnionFind to calculate area of each island and keep track of max area

class MaxAreaOfIsland {
   public:
    static void test() {
        MaxAreaOfIsland obj;
        vector<vector<int>> board = {
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0},
            {1, 1, 0, 0, 1}};

        cout << "Max area of island is: " << obj.maxAreaOfIsland(board) << endl;
    }

   public:
    int maxAreaOfIsland(vector<vector<int>>& board) {
        int areaDFS = maxAreaOfIslandDFS(board);
        int areaDFSIterative = maxAreaOfIslandDFSIterative(board);
        int areaBFS = maxAreaOfIslandBFS(board);
        int areaUnionFind = maxAreaOfIslandUnionFind(board);

        println("Area calculated using DFS: {}, DFS Iterative: {}, BFS: {}, UnionFind: {}", areaDFS, areaDFSIterative, areaBFS, areaUnionFind);

        assert(areaDFS == areaDFSIterative);
        assert(areaDFS == areaBFS);
        assert(areaDFS == areaUnionFind);

        return areaDFS;
    }

   public:
    int maxAreaOfIslandDFS(vector<vector<int>> board) {
        int maxArea = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 1) {
                    maxArea = max(maxArea, area(board, i, j));
                }
            }
        }

        return maxArea;
    }

    int area(vector<vector<int>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[i].size() || board[i][j] == 0) return 0;

        board[i][j] = 0;
        return 1 + area(board, i - 1, j) + area(board, i + 1, j) + area(board, i, j - 1) + area(board, i, j + 1);
    }

   public:
    int maxAreaOfIslandDFSIterative(vector<vector<int>> board) {
        int maxArea = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 1) {
                    maxArea = max(maxArea, areaIterative(board, i, j));
                }
            }
        }

        return maxArea;
    }

    int areaIterative(vector<vector<int>>& board, int i, int j) {
        int area = 0;
        stack<pair<int, int>> s;
        s.push({i, j});

        while (!s.empty()) {
            auto [x, y] = s.top();
            s.pop();

            if (x < 0 || y < 0 || x >= board.size() || y >= board[x].size() || board[x][y] == 0) continue;

            board[x][y] = 0;
            area++;

            s.push({x - 1, y});
            s.push({x + 1, y});
            s.push({x, y - 1});
            s.push({x, y + 1});
        }

        return area;
    }

   public:
    int maxAreaOfIslandBFS(vector<vector<int>> board) {
        int maxArea = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 1) {
                    maxArea = max(maxArea, areaBFS(board, i, j));
                }
            }
        }

        return maxArea;
    }

    int areaBFS(vector<vector<int>>& board, int i, int j) {
        int area = 0;
        queue<pair<int, int>> q;
        q.push({i, j});

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x < 0 || y < 0 || x >= board.size() || y >= board[x].size() || board[x][y] == 0) continue;

            board[x][y] = 0;
            area++;

            q.push({x - 1, y});
            q.push({x + 1, y});
            q.push({x, y - 1});
            q.push({x, y + 1});
        }

        return area;
    }

   public:
    int maxAreaOfIslandUnionFind(vector<vector<int>>& board) {
        int maxArea = 0;
        int n = board.size();
        int m = board[0].size();

        UnionFind uf(n * m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 1) {
                    int k = i * n + j;

                    for (auto& [dx, dy] : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                        int x = i + dx;
                        int y = j + dy;
                        if (x >= 0 && y >= 0 && x < n && y < m && board[x][y] == 1) {
                            uf.Union(k, x * n + y);
                        }
                    }

                    maxArea = max(maxArea, uf.getSize(k));
                }
            }
        }

        return maxArea;
    }

    class UnionFind {
       private:
        vector<int> parent;
        vector<int> size;

       public:
        UnionFind(int n) : parent(n), size(n, 1) {
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            while (parent[x] != x) x = parent[x];

            return parent[x];
        }

        bool Union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);

            if (rootX == rootY) return false;

            if (size[rootX] < size[rootY]) {
                parent[rootX] = rootY;
                size[rootY] += size[rootX];
            } else {
                parent[rootY] = rootX;
                size[rootX] += size[rootY];
            }

            return true;
        }

        int getSize(int x) {
            return size[find(x)];
        }
    };
};