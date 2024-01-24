#pragma once
#include "../header.h"

namespace gfg_sudoku {
#define UNASSIGNED 0 
#define N 9 

    class GFG_SudokuSolver {
    public:
        bool SolveSudoku(IBoard& grid)
        {
            int row, col;

            // If there is no unassigned location, 
            // we are done 
            if (!FindUnassignedLocation(grid, row, col))
                // success! 
                return true;

            // Consider digits 1 to 9 
            for (int num = 1; num <= 9; num++) {
                // if looks promising 
                if (isSafe(grid, row, col, num)) {
                    // make tentative assignment 
                    grid[row][col] = num;

                    // return, if success, yay! 
                    if (SolveSudoku(grid))
                        return true;

                    // failure, unmake & try again 
                    grid[row][col] = UNASSIGNED;
                }
            }
            // this triggers backtracking 
            return false;
        }

        bool isValid(IBoard& board) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int tmp = board[i][j];
                    board[i][j] = UNASSIGNED;
                    if (!isSafe(board, i, j, tmp)) {
                        board[i][j] = tmp;
                        return false;
                    }
                    board[i][j] = tmp;
                }
            }
            return true;
        }

        void printGrid(IBoard& grid)
        {
            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++)
                    cout << grid[row][col] << " ";
                cout << endl;
            }
        }

    private:
        bool FindUnassignedLocation(IBoard& grid,
            int& row, int& col)
        {
            for (row = 0; row < N; row++)
                for (col = 0; col < N; col++)
                    if (grid[row][col] == UNASSIGNED)
                        return true;
            return false;
        }

        bool UsedInRow(IBoard& grid, int row, int num)
        {
            for (int col = 0; col < N; col++)
                if (grid[row][col] == num)
                    return true;
            return false;
        }

        bool UsedInCol(IBoard& grid, int col, int num)
        {
            for (int row = 0; row < N; row++)
                if (grid[row][col] == num)
                    return true;
            return false;
        }

        bool UsedInBox(IBoard& grid, int boxStartRow,
            int boxStartCol, int num)
        {
            for (int row = 0; row < 3; row++)
                for (int col = 0; col < 3; col++)
                    if (grid[row + boxStartRow]
                        [col + boxStartCol]
            == num)
                        return true;
            return false;
        }

        bool isSafe(IBoard& grid, int row,
            int col, int num)
        {
            return !UsedInRow(grid, row, num)
                && !UsedInCol(grid, col, num)
                && !UsedInBox(grid, row - row % 3,
                    col - col % 3, num)
                && grid[row][col] == UNASSIGNED;
        }
    };
}