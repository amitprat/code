#include "../header.h"

class EightQueensProblem {
   public:
    using Board = vector<vector<int>>;
#define QUEEN 1
#define EMPTY 0

    static void test() {
        int n = 8;
        Board board(n, vector<int>(n, EMPTY));
        EightQueensProblem obj;
        obj.placeQueens(board);
    }

   private:
    void placeQueens(Board& board) {
        cout << "Board before: " << endl;
        cout << board << endl;

        bool res = placeQueens(board, 0, board.size());

        if (res) {
            cout << "All queens placed" << endl;
            cout << board << endl;
        } else {
            cout << "All Queens can't be placed." << endl;
        }
    }

    bool placeQueens(Board& board, int col, int n) {
        if (col == n) return true;
        for (int row = 0; row < n; row++) {
            if (canPlace(board, row, col, n)) {
                board[row][col] = QUEEN;
                if (placeQueens(board, col + 1, n)) return true;
                board[row][col] = EMPTY;
            }
        }

        return false;
    }

    bool canPlace(Board& board, int row, int col, int n) {
        // in same row on left side
        for (int i = 0; i < col; i++)
            if (board[row][i] == QUEEN) return false;

        // in top left diag
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == QUEEN) return false;
        }

        // in bottom left diag
        for (int i = row, j = col; i < n && j >= 0; i++, j--) {
            if (board[i][j] == QUEEN) return false;
        }

        return true;
    }
};