#pragma once
#include "../header.h"
#include "../misc/UnionFind.h"

class CountNumberOfIslands {
   public:
    static void test() {
        CountNumberOfIslands obj;
        vector<vector<int>> board = {
            {1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1},
            {1, 0, 0, 1, 1},
            {0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1}};
        int n = board.size();
        int m = board[0].size();

        auto res1 = obj.countIslandsUsingDFS(board, n, m);
        cout << "Islands Uisng DFS = " << res1 << endl;

        auto res2 = obj.countIslandsDisjointSet1(board, n, m);
        cout << "Islands Uisng UnionFind1 = " << res2 << endl;

        auto res3 = obj.countIslandsDisjointSet2(board, n, m);
        cout << "Islands Uisng UnionFind2 = " << res3 << endl;
        assert((res1 == res2) == (res2 == res3));
    }

    int countIslandsUsingDFS(vector<vector<int>> board, int n, int m) {
        int marker = -1;
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 1) {
                    dfs(board, i, j, marker);
                    count++;
                }
            }
        }
        // restore
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == marker) board[i][j] = 1;
            }
        }

        return count;
    }
    int countIslandsDisjointSet1(vector<vector<int>> board, int n, int m) {
        UnionFind* uf;
        uf = new UnionFind(n * m);
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int k = i * n + j;
                if (board[i][j] == 1) {
                    count++;
                    if (j - 1 >= 0 && board[i][j - 1] == 1) {
                        if (uf->Union(k, i * n + j - 1)) count--;
                    }
                    if (i - 1 >= 0 && board[i - 1][j] == 1) {
                        if (uf->Union(k, (i - 1) * n + j)) count--;
                    }
                    if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == 1) {
                        if (uf->Union(k, (i - 1) * n + j - 1)) count--;
                    }
                    if (i - 1 >= 0 && j + 1 < m && board[i - 1][j + 1] == 1) {
                        if (uf->Union(k, (i - 1) * n + j + 1)) count--;
                    }
                }
            }
        }

        return count;
    }
    int countIslandsDisjointSet2(vector<vector<int>> board, int n, int m) {
        UnionFind* uf;
        uf = new UnionFind(n * m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int k = i * n + j;
                if (board[i][j] == 1) {
                    if (j - 1 >= 0 && board[i][j - 1] == 1) uf->Union(k, i * n + j - 1);
                    if (i - 1 >= 0 && board[i - 1][j] == 1) uf->Union(k, (i - 1) * n + j);
                    if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == 1) uf->Union(k, (i - 1) * n + j - 1);
                    if (i - 1 >= 0 && j + 1 < m && board[i - 1][j + 1] == 1) uf->Union(k, (i - 1) * n + j + 1);
                }
            }
        }

        int islands = 0;
        int* parent = new int[n * m];
        memset(parent, 0, n * m * sizeof(int));
        unordered_map<int, vector<pair<int, int>>> islandsList;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 1) {
                    int x = uf->find(i * n + j);
                    if (parent[x] == 0) {
                        islands++;
                    }
                    islandsList[x].push_back({i, j});
                    parent[x]++;
                }
            }
        }

        // debug
        // cout << "[";
        // for (auto i : islandsList) {
        //    cout << "{";
        //    for (auto j : i.second) {
        //        cout << "(" << j.first << ", " << j.second << "), ";
        //    }
        //    cout << "}, ";
        //}
        // cout << "]";

        return islands;
    }

   private:
    void testInner() {
        cout << "----------------------------" << endl;
        ifstream in;
        in.open("input.txt");
        CountNumberOfIslands obj;
        UnionFind* uf = new UnionFind(25);

        auto res = obj.countIslands(in, uf);
        cout << "Islands = " << res << endl;
    }

    void dfs(vector<vector<int>>& board, int i, int j, int marker) {
        board[i][j] = marker;
        for (auto& neighbour : getNeighbours(board, i, j)) {
            dfs(board, neighbour.first, neighbour.second, marker);
        }
    }

    vector<pair<int, int>> getNeighbours(vector<vector<int>>& board, int i, int j) {
        vector<pair<int, int>> result;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (x != y) {
                    int dx = i + x;
                    int dy = j + y;
                    if (isValid(dx, dy, board) && board[dx][dy] == 1) result.push_back({dx, dy});
                }
            }
        }
        return result;
    }

    bool isValid(int x, int y, vector<vector<int>>& board) {
        return x >= 0 && y >= 0 && x < board.size() && y < board[x].size();
    }

    int countIslands(ifstream& in, UnionFind* uf) {
        string line;
        int rowNum = 0;
        vector<int> prevRow;
        int islands = 0;
        while (getline(in, line)) {
            vector<int> row = split(line);
            int rowSize = row.size();
            for (int j = 0; j < rowSize; j++) {
                int k = rowNum * rowSize;
                if (row[j] == 1) {
                    bool isNewIsland = true;
                    if (j - 1 >= 0 && row[j - 1] == 1) {
                        uf->Union(k, rowNum * rowSize + j - 1);
                        isNewIsland = false;
                    }
                    if (prevRow.size()) {
                        if (j - 1 >= 0 && prevRow[j - 1] == 1) {
                            uf->Union(k, rowSize * (rowNum - 1) + j - 1);
                            isNewIsland = false;
                        }
                        if (prevRow[j] == 1) {
                            uf->Union(k, rowSize * (rowNum - 1) + j);
                            isNewIsland = false;
                        }
                        if (j + 1 < rowSize && prevRow[j + 1] == 1) {
                            uf->Union(k, rowSize * (rowNum - 1) + j + 1);
                            isNewIsland = false;
                        }
                    }
                    if (isNewIsland) {
                        islands++;
                    }
                }
            }
            prevRow = row;
            rowNum++;
        }
        // cout << uf->toString(prevRow.size());

        return islands;
    }

    vector<int> split(string str) {
        vector<int> res;
        size_t pos = string::npos;
        int start = 0;
        do {
            pos = str.find(' ');
            string tmp = str.substr(start, pos);
            res.push_back(stoi(tmp));
            if (pos != string::npos) str = str.substr(pos + 1);
        } while (pos != string::npos);

        return res;
    }
};