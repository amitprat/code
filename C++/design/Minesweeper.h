#pragma once
#include "../Header.h"

class Minesweeper {
    struct Node {
        int adj = 0;
        bool seen = false;
        string to_string() {
            return "{" + std::to_string(adj) + "," + std::to_string(seen) + "}";
        }
    };
    vector<Node> board;
    int rows, cols, mines;
    const int mine = 9;
public:
    Minesweeper(int rows, int cols, int mines) {
        this->rows = rows;
        this->cols = cols;
        this->mines = mines;
    }
    static void test() {
        srand(time(nullptr));
        Minesweeper obj(4, 4, 1);
        auto status = obj.init();
        while (status) {
            obj.print();
            int rr = rand() % 4;
            int rc = rand() % 4;
            cout << "Stepping on pos = " << rr << "," << rc << endl;
            status = obj.onClick(rr, rc);
            obj.print();
            cout << endl;
        }
    }
    bool init() {
        if (mines >= rows * cols) return false;
        board.resize(rows * cols);
        for (int i = 0; i < mines; i++) board[i] = { mine,false };
        for (int r = mines; r < board.size(); r++) {
            int pos = rand() % r;
            if (pos < mines) swap(board[pos], board[r]);
        }

        for (int i = 0; i < board.size(); i++) {
            if (board[i].adj == mine) {
                for (int j = -1; j <= 1; j++) {
                    for (int k = -1; k <= 1; k++) {
                        if (j != 0 || k != 0) {
                            int pos = i + cols * j + k;
                            if (pos < 0 || pos >= board.size() || board[pos].adj == mine) continue;
                            board[pos].adj += 1;
                        }
                    }
                }
            }
        }

        return true;
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << setw(7) << get(i, j).to_string() << " ";
            }
            cout << endl;
        }
    }

    bool onClick(int row, int col) {
        if (row < 0 || col < 0 || row >= rows || col >= cols) return true;
        int pos = row * cols + col;
        if (board[pos].seen) return true;
        if (board[pos].adj == mine) {
            cout << "Stepped on mine (BOOOOM)..." << endl;
            return false;
        }
        explore(row, col);
        return true;
    }

    void explore(int row, int col) {
        if (row < 0 || col < 0 || row >= rows || col >= cols) return;
        int pos = row * cols + col;
        if (board[pos].seen) return;
        board[pos].seen = true;
        if (board[pos].adj != 0) return;
        explore(row - 1, col);
        explore(row + 1, col);
        explore(row, col - 1);
        explore(row, col + 1);
    }

    Node get(int row, int col) {
        int pos = row * cols + col;
        return board[pos];
    }
};