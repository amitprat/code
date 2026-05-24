#pragma once
#include "../header.h"
using namespace std;

class ValidateSuduko {
   public:
    static void test() {
        ValidateSuduko obj;
        vector<vector<char>> board = {
            {'.', '1', '3', '.', '.', '8', '.', '2', '5'},
            {'.', '9', '.', '7', '.', '.', '1', '3', '.'},
            {'5', '.', '6', '.', '.', '.', '9', '.', '.'},
            {'.', '.', '2', '.', '.', '.', '8', '9', '1'},
            {'8', '.', '1', '6', '.', '.', '5', '.', '3'},
            {'.', '6', '1', '.', '.', '.', '.', '.', '.'},
            {'1', '2', '8', '.', '.', '.', '3', '.', '.'},
            {'.', '.', '.', '.', '.', '.', '4', '1', '.'},
            {'9', '3', '.', '.', '.', '.', '2', '8', '7'},
        };
        cout << obj.isValidSudoku1(board) << endl;
    }

   public:
    bool isValidSudoku1(vector<vector<char>>& board) {
        int n = board.size();
        vector<unordered_set<int>> rows(n);
        vector<unordered_set<int>> cols(n);
        vector<unordered_set<int>> blocks(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') continue;
                auto num = board[i][j] - '0';
                int b = (i / 3) * 3 + (j / 3);
                if (rows[i].contains(num) || cols[j].contains(num) || blocks[b].contains(num)) {
                    return false;
                }
                rows[i].insert(num);
                cols[j].insert(num);
                blocks[b].insert(num);
            }
        }

        return true;
    }

   public:
    bool isValidSudoku2(vector<vector<char>>& board) {
        bool rows[9][9] = {false};
        bool cols[9][9] = {false};
        bool boxes[9][9] = {false};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0';
                    int boxIndex = (i / 3) * 3 + (j / 3);
                    if (rows[i][num] || cols[j][num] || boxes[boxIndex][num]) return false;
                    rows[i][num] = cols[j][num] = boxes[boxIndex][num] = true;
                }
            }
        }
        return true;
    }

   public:
    bool isValidSudoku3(vector<vector<char>>& board) {
        int n = board.size();
        bitset<9> rows[9];
        bitset<9> cols[9];
        bitset<9> blocks[9];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') continue;
                auto num = board[i][j] - '0';
                int b = (i / 3) * 3 + (j / 3);
                if (rows[i][num] || cols[j][num] || blocks[b][num]) {
                    return false;
                }
                rows[i][num] = cols[j][num] = blocks[b][num] = true;
            }
        }

        return true;
    }

   public:
    bool isValidSudoku4(vector<vector<char>>& board) {
        int n = board.size();
        vector<int> rows(n + 1, 0);
        vector<int> cols(n + 1, 0);
        vector<int> blocks(n + 1, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') continue;

                auto num = board[i][j] - '0';
                int b = (i / 3) * 3 + (j / 3);

                if ((rows[i] & (1 << num)) || (cols[j] & (1 << num)) || (blocks[b] & (1 << num))) {
                    return false;
                }

                rows[i] |= (1 << num);
                cols[j] |= (1 << num);
                blocks[b] |= (1 << num);
            }
        }
    }
};