#pragma once
#include "../header.h"

class EightQueen {
private:
    int N = 8;
    int board[8][8];
public:
    static void test() {
        EightQueen obj;
        cout << "Num ways to place queen:" << obj.getNumWays() << endl;
    }

    EightQueen() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                board[i][j] = -1;
            }
        }
    }

    int getNumWays() {
        vector<int> columns(N, -1);
        vector<vector<int>> result;

        getNumWays(0, columns, result);
        print(result);
        return result.size();
    }

    bool getNumWays(int row, vector<int> columns, vector<vector<int>>& result) {
        if (row == N) {
            result.push_back(columns);
            return true;
        }
        for (int col = 0; col < N; col++) {
            if (isValid(row, col)) {
                columns[row] = col;
                getNumWays(row + 1, columns, result);
                columns[row] = -1;
            }
        }
        return false;
    }

    bool isValid(int row, int col) {
        // check above this row
        for (int i = 0; i < row; i++) {
            if (board[i][col] != -1) return false;
        }
        // check left upper diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] != -1) return false;
        }

        // check right upper diagonal
        for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
            if (board[i][j] != -1) return false;
        }

        return true;
    }
};