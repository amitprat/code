#pragma once
#include "../header.h"

class SurroundedRegions {
public:
    static void test() {
        SurroundedRegions obj;
        vector<vector<char>> test = {
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}
        };

        vector<vector<char>> expected = {
            {'X', 'X', 'X', 'X'},
            {'X', 'X', 'X', 'X'},
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'X', 'X'}
        };

        auto copy = test;
        obj.captureRegion(copy);
        assert(AreEqual(copy, expected));

        copy = test;
        obj.captureRegion2(copy);
        assert(AreEqual(copy, expected));
    }

    void captureRegion(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        char find = 'O';
        char marker = '$';

        // mark top and bottom row with marker
        for (int j = 0; j < m; j++) {
            if (board[0][j] == find) dfs(board, 0, j, find, marker);
            if (board[n - 1][j] == find) dfs(board, n - 1, j, find, marker);
        }

        // mark left and right columns with marker
        for (int i = 0; i < n; i++) {
            if (board[i][0] == find) dfs(board, i, 0, find, marker);
            if (board[i][m - 1] == find) dfs(board, i, m - 1, find, marker);
        }

        // process board
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == find) board[i][j] = 'X';
                else if (board[i][j] == marker) board[i][j] = find;
            }
        }
    }

    void captureRegion2(vector<vector<char>>& board)
    {
        char find = 'O';
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == find) {
                    dfs2(board, i, j, find);
                }
            }
        }
    }
private:
    void dfs(vector<vector<char>>& board, int i, int j, char find, char marker) {
        board[i][j] = marker;
        for (auto& neighbour : getNeighbours(board, i, j, find)) {
            dfs(board, neighbour.first, neighbour.second, find, marker);
        }
    }

    bool dfs2(vector<vector<char>>& board, int i, int j, char find) {
        if (!isValid(board, i, j)) return false;
        if (board[i][j] == 'X') return true;
        board[i][j] = 'X';
        for (auto& neighbour : getNeighbours2(board, i, j)) {
            if (!dfs2(board, neighbour.first, neighbour.second, find)) {
                board[i][j] = find;
                return false;
            }
        }
        return true;
    }

    vector<pair<int, int>> getNeighbours(vector<vector<char>>& board, int i, int j, char find)
    {
        vector<pair<int, int>> result;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (abs(x) != abs(y)) {
                    int dx = i + x;
                    int dy = j + y;
                    if (isValid(board, dx, dy) && board[dx][dy] == find) {
                        result.push_back({ dx, dy });
                    }
                }
            }
        }

        return result;
    }

    vector<pair<int, int>> getNeighbours2(vector<vector<char>>& board, int i, int j)
    {
        vector<pair<int, int>> result;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (abs(x) != abs(y)) {
                    int dx = i + x;
                    int dy = j + y;
                    result.push_back({ dx, dy });
                }
            }
        }

        return result;
    }

    bool isValid(vector<vector<char>>& board, int i, int j) {
        return i >= 0 && j >= 0 && i < board.size() && j < board[0].size();
    }

    static bool AreEqual(vector<vector<char>>& board1, vector<vector<char>>& board2) {
        for (int i = 0; i < board1.size(); i++) {
            for (int j = 0; j < board1[i].size(); j++) {
                if (board1[i][j] != board2[i][j]) return false;
            }
        }
        return true;
    }
};