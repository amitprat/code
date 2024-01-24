#pragma once
#include "../header.h"

using namespace std;
#define N 9
#define M 3
#define UNASSIGNED 0

class SolveAndValidateSudoku
{
public:
    static void test() {
        SolveAndValidateSudoku obj;

        {
            int grid[N][N] = {
                { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                { 0, 0, 5, 2, 0, 6, 3, 0, 0 }
            };

            cout << "Original Sudoku:=>" << endl;
            obj.printGrid(grid);

            cout << "Solved Sudoku:=>" << endl;
            if (obj.SolveSudokuOptimized(grid) == true) {
                if (!obj.ValidateSudoku(grid)) {
                    cout << "Sudoku solution is invalid" << endl;
                }
                else {
                    obj.printGrid(grid);
                }
            }
            else {
                cout << "No solution exists for given Sudoku board." << endl;
            }
        }

        {
            int grid[N][N] = {
                { 3, 1, 6, 5, 7, 8, 4, 9, 2 },
                { 5, 2, 9, 1, 3, 4, 7, 6, 8 },
                { 4, 8, 7, 6, 2, 9, 5, 3, 1 },
                { 2, 6, 3, 0, 1, 5, 9, 8, 7 },
                { 9, 7, 4, 8, 6, 0, 1, 2, 5 },
                { 8, 5, 1, 7, 9, 2, 6, 4, 3 },
                { 1, 3, 8, 0, 4, 7, 2, 0, 6 },
                { 6, 9, 2, 3, 5, 1, 8, 7, 4 },
            };

            cout << "Original Sudoku:=>" << endl;
            obj.printGrid(grid);

            cout << "Solved Sudoku:=>" << endl;
            if (obj.SolveSudokuOptimized(grid) == true) {
                if (!obj.ValidateSudoku(grid)) {
                    cout << "Sudoku solution is invalid" << endl;
                }
                else {
                    obj.printGrid(grid);
                }
            }
            else {
                cout << "No solution exists for given Sudoku board." << endl;
            }
        }
    }

    bool SolveSudoku(int grid[N][N]) {
        int row = -1, col = -1;
        if (!findUnassignedLocation(grid, row, col)) return true;
        for (int num = 1; num <= N; num++) {
            if (isSafe(grid, row, col, num)) {
                grid[row][col] = num;
                if (SolveSudoku(grid)) return true;
                grid[row][col] = UNASSIGNED;
            }
        }
        return false;
    }

    bool SolveSudokuOptimized(int grid[N][N]) {
        unordered_set<int> emptyBlocks;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == 0) {
                    emptyBlocks.insert(i * N + j);
                }
            }
        }

        return SolveSudokuOptimized(grid, emptyBlocks);
    }

    bool SolveSudokuOptimized(int grid[N][N], unordered_set<int>& emptyBlocks) {
        if (emptyBlocks.empty()) return true;

        auto pos = *emptyBlocks.begin();
        int x = pos / N, y = pos % N;
        emptyBlocks.erase(emptyBlocks.begin());

        for (int num = 1; num <= N; num++) {
            if (isSafe(grid, x, y, num)) {
                grid[x][y] = num;
                if (SolveSudokuOptimized(grid, emptyBlocks)) return true;
                grid[x][y] = 0;
            }
        }
        emptyBlocks.insert(pos);

        return false;
    }

    bool ValidateSudoku(int grid[N][N]) {
        unordered_set<string> seen;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int number = grid[i][j];
                if (number == 0) return false;

                string key = to_string(number) + " in row " + to_string(i);
                if (!seen.insert(key).second) {
                    cout << format("Found invalid value {} in sudoku board", key) << endl;
                    return false;
                }

                key = to_string(number) + " in column " + to_string(j);
                if (!seen.insert(key).second) {
                    cout << format("Found invalid value {} in sudoku board", key) << endl;
                    return false;
                }

                key = to_string(number) + " in block " + to_string(i / 3) + "-" + to_string(j / 3);
                if (!seen.insert(key).second) {
                    cout << format("Found invalid value {} in sudoku board", key) << endl;
                    return false;
                }
            }
        }

        return true;
    }

private:
    void printGrid(int grid[N][N])
    {
        vector<string> str;
        for (int i = 0; i < N; i++) {
            drawHorizontal(i);
            for (int j = 0; j < N; j++) {
                if (j % M == 0) cout << setw(2) << "|";
                string out = std::to_string(grid[i][j]);
                out = out == "0" ? " " : out;
                cout << setw(2) << out << " ";
            }
            cout << "|" << endl;
        }
        drawHorizontal(N);
    }

    bool findUnassignedLocation(int grid[][N], int& row, int& col) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == UNASSIGNED) {
                    row = i;
                    col = j;
                    return true;
                }
            }
        }
        return false;
    }

    bool isSafe(int grid[][N], int row, int col, int num) {
        // check row
        for (int j = 0; j < N; j++) {
            if (grid[row][j] == num) return false;
        }

        // check col
        for (int i = 0; i < N; i++) {
            if (grid[i][col] == num) return false;
        }

        // check subsquare
        int subrowstart = row - row % M;
        int subrowend = subrowstart + M;
        int subcolstart = col - col % M;
        int subcolend = subcolstart + M;

        for (int i = subrowstart; i < subrowend; i++) {
            for (int j = subcolstart; j < subcolend; j++) {
                if (grid[i][j] == num) return false;
            }
        }

        return true;
    }

    void drawHorizontal(int i) {
        if (i % M == 0) {
            cout << " ";
            for (int j = 0; j < N; j++) {
                cout << "---";
            }
            for (int j = 0; j < N - 3; j++) {
                cout << "-";
            }
            cout << endl;
        }
    }
};