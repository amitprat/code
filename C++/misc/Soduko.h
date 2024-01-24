#pragma once
#include "../header.h"

using namespace std;
#define N 9
#define M 3
#define UNASSIGNED 0

class SodokuSolver
{
public:
    static void test() {
        SodokuSolver obj;
        int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                   { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                   { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                   { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                   { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                   { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                   { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                   { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                   { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

        cout << "Original Soduko:=>" << endl;
        obj.printGrid(grid);

        cout << "Solved Soduko:=>" << endl;
        if (obj.SolveSudoku(grid) == true)
            obj.printGrid(grid);
        else
            cout << "No solution exists";
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