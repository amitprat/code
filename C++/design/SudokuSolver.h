#pragma once
#include "../header.h"

class SudokuSolver {
    using IBoard = vector<vector<int>>;
    const int UNASSIGNED = 0;

   public:
    static void test() {
        SudokuSolver obj;
        IBoard board = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                        {5, 2, 0, 0, 0, 0, 0, 0, 0},
                        {0, 8, 7, 0, 0, 0, 0, 3, 1},
                        {0, 0, 3, 0, 1, 0, 0, 8, 0},
                        {9, 0, 0, 8, 6, 3, 0, 0, 5},
                        {0, 5, 0, 0, 9, 0, 6, 0, 0},
                        {1, 3, 0, 0, 0, 0, 2, 5, 0},
                        {0, 0, 0, 0, 0, 0, 0, 7, 4},
                        {0, 0, 5, 2, 0, 6, 3, 0, 0}};

        auto res = obj.SolveSudoku(board);
        cout << "Can be solved: " << res << endl;

        cout << "Solved sudoku:" << endl;
        cout << board << endl;

        auto isvalid = obj.isValid(board);
        cout << "Is valid board: " << isvalid << endl;
    }

   public:
    bool SolveSudoku(IBoard& board) {
        int row, col;

        // If there is no unassigned location, return success.
        if (!FindUnassignedLocation(board, row, col))
            return true;

        // Consider digits 1 to 9
        for (int num = 1; num <= 9; num++) {
            if (isSafe(board, row, col, num)) {
                // make tentative assignment
                board[row][col] = num;

                // return, if success, yay!
                if (SolveSudoku(board))
                    return true;

                // failure, unmake & try again
                board[row][col] = UNASSIGNED;
            }
        }

        // this triggers backtracking
        return false;
    }

    // check if given board is valid board
    bool isValid(IBoard& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                // cache element at current position and make current position as unassigned.
                int tmp = board[i][j];
                board[i][j] = UNASSIGNED;

                // try to assign current element and see if it is valid element.
                if (!isSafe(board, i, j, tmp)) {
                    board[i][j] = tmp;
                    return false;
                }

                // reset the element at current position.
                board[i][j] = tmp;
            }
        }
        return true;
    }

   private:
    bool FindUnassignedLocation(IBoard& board, int& row, int& col) {
        for (row = 0; row < board.size(); row++)
            for (col = 0; col < board[row].size(); col++)
                if (board[row][col] == UNASSIGNED)
                    return true;

        return false;
    }

    bool isSafe(IBoard& grid, int row, int col, int num) {
        return !UsedInRow(grid, row, num) &&
               !UsedInCol(grid, col, num) &&
               !UsedInBox(grid, row - row % 3, col - col % 3, num) &&
               grid[row][col] == UNASSIGNED;
    }

    bool UsedInRow(IBoard& board, int row, int num) {
        for (int col = 0; col < board.size(); col++)
            if (board[row][col] == num)
                return true;

        return false;
    }

    bool UsedInCol(IBoard& board, int col, int num) {
        for (int row = 0; row < board.size(); row++)
            if (board[row][col] == num)
                return true;

        return false;
    }

    bool UsedInBox(IBoard& grid, int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; row++)
            for (int col = 0; col < 3; col++)
                if (grid[row + boxStartRow][col + boxStartCol] == num)
                    return true;

        return false;
    }

   private:
    bool SolveSudokuOptimized(IBoard& board) {
        unordered_set<int> emptyBlocks;
        int N = board.size();
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 0) {
                    emptyBlocks.insert(i * N + j);
                }
            }
        }

        return SolveSudokuOptimized(board, emptyBlocks);
    }

    bool SolveSudokuOptimized(IBoard& board, unordered_set<int>& emptyBlocks) {
        if (emptyBlocks.empty()) return true;

        int N = board.size();
        auto pos = *emptyBlocks.begin();
        int x = pos / N, y = pos % N;
        emptyBlocks.erase(emptyBlocks.begin());

        for (int num = 1; num <= N; num++) {
            if (isSafe(board, x, y, num)) {
                board[x][y] = num;
                if (SolveSudokuOptimized(board, emptyBlocks)) return true;
                board[x][y] = 0;
            }
        }
        emptyBlocks.insert(pos);

        return false;
    }

   public:
    bool solveSudoku(IBoard& board) {
        int n = board.size();
        vector<bool> rows(n, false), cols(n, false), blocks(n, false);

        vector<pair<int, int>> emptySlots;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == UNASSIGNED) emptySlots.push_back({i, j});
            }
        }

        return solveSudoku(board, n, emptySlots, 0, emptySlots.size(), rows, cols, blocks);
    }

    bool solveSudoku(IBoard& board, int n, vector<pair<int, int>>& emptySlots, int index, int m,
                     vector<bool>& rows, vector<bool>& cols, vector<bool>& blocks) {
        if (index == m) return true;

        auto slot = emptySlots[index];

        for (int num = 1; num <= 9; num++) {
            if (!rows[slot.first] && !cols[slot.second] && !blocks[(slot.first / n) * n + slot.second]) {
                rows[slot.first] = cols[slot.second] = blocks[(slot.first / n) * n + slot.second] = true;
                board[slot.first][slot.second] = num;

                if (solveSudoku(board, n, emptySlots, index + 1, m, rows, cols, blocks)) return true;

                rows[slot.first] = cols[slot.second] = blocks[(slot.first / n) * n + slot.second] = false;
                board[slot.first][slot.second] = UNASSIGNED;
            }
        }

        return false;
    }

   public:
    void solveSudoku(vector<vector<char>>& board) {
        bitset<10> rows[9], cols[9], blocks[9];  // for keeping track of used numbers in rows, columns and 3x3 blocks
        vector<pair<int, int>> emptySlots;       // to store the positions of empty cells

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == '.') emptySlots.push_back({i, j});  // if empty, add to emptySlots
                else {
                    // if not empty, mark the number as used in corresponding row, column and block
                    rows[i].set(board[i][j] - '0');
                    cols[j].set(board[i][j] - '0');
                    blocks[(i / 3) * 3 + (j / 3)].set(board[i][j] - '0');
                }
            }
        }

        bool result = solveSudoku(board, emptySlots, rows, cols, blocks);
        if (!result) cout << "Couldn't solve it" << endl;
    }

    bool solveSudoku(vector<vector<char>>& board, vector<pair<int, int>>& emptySlots,
                     bitset<10> (&rows)[9], bitset<10> (&cols)[9], bitset<10> (&blocks)[9]) {
        // if there are no more empty slots, we have successfully solved the sudoku
        if (emptySlots.empty()) return true;

        // get the next empty slot to fill
        auto slot = emptySlots.back();
        emptySlots.pop_back();

        for (int num = 1; num <= 9; num++) {
            // check if it's safe to place the number in the current slot (i.e., it doesn't violate sudoku rules)
            if (!rows[slot.first].test(num) &&
                !cols[slot.second].test(num) &&
                !blocks[(slot.first / 3) * 3 + (slot.second / 3)].test(num)) {
                // if it's safe, place the number and mark it as used in the corresponding row, column and block
                board[slot.first][slot.second] = num + '0';
                rows[slot.first].set(num);
                cols[slot.second].set(num);
                blocks[(slot.first / 3) * 3 + (slot.second / 3)].set(num);

                // recursively try to solve the rest of the sudoku with the current number placed
                if (solveSudoku(board, emptySlots, rows, cols, blocks)) return true;

                // if placing the number doesn't lead to a solution, backtrack: unmark the number and reset the slot
                board[slot.first][slot.second] = '.';
                rows[slot.first].reset(num);
                cols[slot.second].reset(num);
                blocks[(slot.first / 3) * 3 + (slot.second / 3)].reset(num);
            }
        }

        // if no number from 1 to 9 can be placed in the current slot, backtrack by adding the slot back to emptySlots and return false
        emptySlots.push_back(slot);

        return false;
    }
};