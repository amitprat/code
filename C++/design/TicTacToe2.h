#pragma once
#include "../Header.h"

class TicTacToePrinter {
    string top, bottom, middle;
    char vals[3][3];
public:
    TicTacToePrinter() {
        top = bottom = middle = "----------";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                vals[i][j] = ' ';
            }
        }
    }
    void set(int pos, char val) {
        vals[pos / 3][pos % 3] = val;
    }

    string to_string() {
        stringstream ss;

        ss << top << endl;

        for (int i = 0; i < 3; i++) {
            ss << "|" << vals[0][i] << " ";
        }
        ss << "|" << endl;

        ss << middle << endl;

        for (int i = 0; i < 3; i++) {
            ss << "|" << vals[1][i] << " ";
        }
        ss << "|" << endl;

        ss << middle << endl;

        for (int i = 0; i < 3; i++) {
            ss << "|" << vals[2][i] << " ";
        }
        ss << "|" << endl;

        ss << bottom << endl;

        return ss.str();
    }
};

class TicTacToeStore {

};

class TicTacToeBoard {
    vector<char> board;
    TicTacToePrinter printer;
    TicTacToeStore store;
public:
    TicTacToeBoard() {
        for (int i = 0; i < 9; i++) board.push_back(' ');
    }
    void set(int x, int y, char ch) {
        board[x * y] = ch;
    }
    string to_string() {
        for (int i = 0; i < 9; i++) printer.set(i, board[i]);
        return printer.to_string();
    }
    bool hasValidMove() {
        string boardStr = getBoardString();
        return !store.isTie(boardStr) && !store.isEnd(boardStr);
    }
    bool hasWon() {
        return store.isEnd(boardStr);
    }
    char wonSymbol() {
        for (int i = 0; i < 3; i++) {
            if (board[0 + i] == board[3 + i] && board[3 + i] == board[6 + i])
                return board[i];
        }
        for (int i = 0; i < 3; i+=3) {
            if (board[0 + i] == board[1 + i] && board[1 + i] == board[2 + i])
                return board[i];
        }
        for (int i = 0; i < 3; i += 3) {
            if (board[0 + i] == board[1 + i] && board[1 + i] == board[2 + i])
                return board[i];
        }

        if (board[0] == board[4] && board[4] == board[8]) return board[0];
        if (board[2] == board[4] && board[4] == board[6]) return board[0];

        return '#';
    }

    string getBoardString() {
        string str;
        for (int i = 0; i < 9; i++) str += board[i];
        return str;
    }
};
class TicTacToe {
public:
    static void test() {
        TicTacToeBoard board;
        cout << board.to_string() << endl;
        

        while (board.hasValidMove()) {
            int x, y;
            char ch;
            cout << "Pos=";
            cin >> x;
            cout << ", ";
            cin >> y;
            cout << " = char = ";
            cin >> ch;

            board.set(x, y, ch);
        }
        if (board.hasWon()) {
            cout << "Won symbol = " << board.wonSymbol() << endl;
        }
        if (board.isTie()) {
            cout << "Board is a tie" << endl;
        }
        cout << board.to_string() << endl;
    }
};

