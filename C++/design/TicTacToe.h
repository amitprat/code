#pragma once
#include "../header.h"

class GameBoard {
public:
    static const int SIZE = 3;
    static enum class State { NONE, WIN, TIE };
    static const char MARKER_EMPTY = '#';
    static const char MARKER_O = '0';
    static const char MARKER_X = 'X';

private:
    CBoard board;

public:
    GameBoard() {}
    void Init() {
        board.resize(SIZE);
        for (int i = 0; i < SIZE; i++) {
            board[i].resize(SIZE);
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = MARKER_EMPTY;
            }
        }
    }

    void Reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = MARKER_EMPTY;
            }
        }
    }
    void updateBoard(int x, int y, char marker) {
        board[x][y] = marker;
    }

    State getState(pair<int, int> pos, char marker) {
        bool res = InSameRow(pos, marker) || InSameColumn(pos, marker) || InSameDiag(marker);
        if (res == true) return State::WIN;
        if (getAllValidPositions(MARKER_EMPTY).empty()) return State::TIE;
        return State::NONE;
    }

    vector<pair<int, int>> getAllValidPositions(char marker) {
        vector<pair<int, int>> result;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == MARKER_EMPTY) result.push_back({ i,j });
            }
        }
        return result;
    }
    string to_string() {
        return ::to_string(board);
    }

    CBoard getRaw() {
        return board;
    }

private:
    bool InSameRow(pair<int, int> pos, char marker) {
        for (int j = 0; j < SIZE; j++) if (board[pos.first][j] != marker) return false;
        return true;
    }

    bool InSameColumn(pair<int, int> pos, char marker) {
        for (int i = 0; i < SIZE; i++) if (board[i][pos.second] != marker) return false;
        return true;
    }

    bool InSameDiag(char marker) {
        for (int i = 0, j = 0; i < SIZE && j < SIZE; i++, j++) if (board[i][j] != marker) return false;
        for (int i = 0, j = SIZE - 1; i < SIZE && j >= 0; i++, j--) if (board[i][j] != marker) return false;
        return true;
    }
};

class Player {
private:
    GameBoard& board;
    char color;
    string name;
    int totalMatchCounts = 0;
    int winCounts = 0;
    vector<CBoard> winningBoards;
    bool isGameInProgress = false;
    vector<pair<int, int>> mypositions;

public:
    Player(GameBoard& board) : board(board) {}
    void init(char color, string name) {
        this->color = color;
        this->name = name;
    }

    pair<int, int> makeMove() {
        if (!isGameInProgress) {
            isGameInProgress = true;
            totalMatchCounts++;
        }
        pair<int, int> pos = getNextPosition();
        mypositions.push_back(pos);
        board.updateBoard(pos.first, pos.second, color);
        return pos;
    }

    pair<int, int> getNextPosition() {
        vector<pair<int, int>> positions = board.getAllValidPositions(color);
        //double winningProb = getWinningProb(positions);
        //double getOppWinningProb = getWinningProb(MAKER_X);
        return getPositionWithMaxWinningProb(positions);
    }

    string to_string() {
        stringstream ss;
        ss << "Player :" << name << endl;
        ss << "Color : " << color << endl;
        ss << "Total Matches: " << totalMatchCounts << endl;
        ss << "Winning Matches: " << winCounts << endl;
        ss << endl;
        return ss.str();
    }

    char getColor() {
        return color;
    }

    void markWinner() {
        cout << "Yey, " << name << " won then game!!" << endl;
        sort(mypositions.begin(), mypositions.end(), [](auto& first, auto& second) {return first.first <= second.first && first.second <= second.second; });
        cout << "Winning positions" << ::to_string(mypositions) << endl;
        mypositions.clear();
        isGameInProgress = false;
        winCounts++;
        winningBoards.push_back(board.getRaw());
    }

    void markLoser() {
        mypositions.clear();
        cout << "You sucker " << name << ", play better next time!!" << endl;
        isGameInProgress = false;
    }

private:
    pair<int, int> getPositionWithMaxWinningProb(vector<pair<int, int>> positions) {
        int r = rand() % positions.size();
        return positions[r];
    }
};

class TicTacToe {
private:
    GameBoard board;
    Player* player1 = nullptr, * player2 = nullptr;
    Player* currentPlayer = nullptr;

public:
    TicTacToe() {
        srand(time(nullptr));
        player1 = new Player(board);
        player2 = new Player(board);
        player1->init(GameBoard::MARKER_O, "Player1");
        player2->init(GameBoard::MARKER_X, "Player2");
    }

    void start() {
        board.Init();

        updateTurn();
        play();
    }

    void play() {
        cout << currentPlayer->to_string() << endl;
        auto pos = currentPlayer->makeMove();
        cout << board.to_string() << endl;

        switch (board.getState(pos, currentPlayer->getColor())) {
            case GameBoard::State::WIN:
                currentPlayer->markWinner();
                if (currentPlayer == player1) player2->markLoser();
                else player1->markLoser();
                if (getUserInput("Would you like to play more??")) start();
                else stop();
                break;
            case GameBoard::State::TIE:
                cout << "Ah, game tie!" << endl;
                if (getUserInput("Would you like to play more??")) start();
                else stop();
                break;
            case GameBoard::State::NONE:
                updateTurn();
                play();
                break;
        }
    }

    bool getUserInput(string initial) {
        char ch;
        cout << initial;
        cin >> ch;
        if (toupper(ch) != 'Y' && toupper(ch) != 'N') {
            cout << "Invalid User Input, Please enter(Y/N)??" << endl;
            return getUserInput(initial);
        }
        return toupper(ch) == 'Y';
    }

    void stop() {
        // show game stats
        cout << player1->to_string() << endl;
        cout << player2->to_string() << endl;

        cout << "Thanks for playing!!";
        cout << endl;
    }


    void updateTurn() {
        if (currentPlayer == nullptr) {
            currentPlayer = player1;
        }
        else if (currentPlayer == player1) {
            currentPlayer = player2;
        }
        else {
            currentPlayer = player1;
        }
    }
};