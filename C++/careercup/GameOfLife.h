#pragma once
#include "../header.h"

class GameOfLife {
   public:
    static void test() {
        GameOfLife obj;
        vector<vector<int>> board = {{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}};
        cout << board << endl;

        obj.gameOfLife(board);
        cout << board << endl;
    }

   public:
    void gameOfLife(vector<vector<int>>& board) {
        if (board.empty()) return;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                const auto& [live, dead] = getNeighbours(board, i, j);

                if (board[i][j] == 1 && live < 2) board[i][j] = -1;
                else if (board[i][j] == 1 && (live == 2 || live == 3)) board[i][j] = 1;
                else if (board[i][j] == 1 && live > 3) board[i][j] = -1;
                else if (!board[i][j] && live == 3) board[i][j] = 2;
            }
        }
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] > 0) board[i][j] = 1;
                else board[i][j] = 0;
            }
        }
    }

    pair<int, int> getNeighbours(vector<vector<int>>& board, int row, int col) {
        pair<int, int> liveDead = {0, 0};
        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                if (r == 0 && c == 0) continue;

                int nr = row + r;
                int nc = col + c;
                if (nr < 0 || nc < 0 || nr >= board.size() || nc >= board[0].size()) continue;

                if (abs(board[nr][nc]) == 1) liveDead.first++;
                else if (board[nr][nc] == 0) liveDead.second++;
            }
        }

        return liveDead;
    }
};