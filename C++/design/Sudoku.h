#pragma once
#include "../header.h"
#include "../design/GFG_SudokuSolver.h"

namespace sudoku {
    static const int SIZE = 9;
    static const int BOXSIZE = 3;
    static const int MARKER_EMPTY = 0;

    class Move {
    public:
        Position pos;
        int num;
        Move() {}
        Move(Position pos, int num) : pos(pos), num(num) {}
    };

    class SudokuSolver {
    public:
        bool hasExtactOneSol(IBoard& board) {
            IBoard copy = board;
            int count = 0;
            return !hasMultipleSolution(copy, count);
        }

    private:
        bool hasMultipleSolution(IBoard& board, int& count) {
            Position pos;
            if (!hasNextEmptyPosition(board, pos)) { count++; return true; }
            for (int num = 1; num <= SIZE; num++) {
                if (isValid(board, pos, num)) {
                    board[pos.x][pos.y] = num;
                    if (hasMultipleSolution(board, count) && count >= 2) return true;
                    board[pos.x][pos.y] = MARKER_EMPTY;
                }
            }
            return false;
        }

        bool hasNextEmptyPosition(IBoard& board, Position& pos) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == MARKER_EMPTY) { pos = { i,j }; return true; }
                }
            }
            return false;
        }

        bool isValid(IBoard& board, Position& pos, int num) {
            //check row
            for (int j = 0; j < SIZE; j++) {
                if (board[pos.x][j] == num) return false;
            }

            // check column
            for (int i = 0; i < SIZE; i++) {
                if (board[i][pos.y] == num) return false;
            }

            // check box
            int dx = pos.x - pos.x % BOXSIZE;
            int dy = pos.y - pos.y % BOXSIZE;
            for (int i = 0; i < BOXSIZE; i++) {
                for (int j = 0; j < BOXSIZE; j++) {
                    if (board[dx + i][dy + j] == num) return false;
                }
            }

            return true;
        }
    };

    class SudokuGenerator {
    public:
        enum class Level { EASY, MEDIUM, HARD };

    private:
        SudokuSolver solver;
        int emptyCells[3] = { 5, 12, 19 };

    public:
        void generate(IBoard& board, Level level) {
            auto res = generateFullBoard(board);
            int curEmptyCells = 0;
            if (res == false) return;
            do {
                Position pos = randomPosition(board);
                board[pos.x][pos.y] = MARKER_EMPTY;
                curEmptyCells++;
            } while (curEmptyCells < emptyCells[(int)level] || !solver.hasExtactOneSol(board));
            cout << "Missing cells: " << curEmptyCells << endl;
        }

        bool generateFullBoard(IBoard& board) {
            Position pos;
            if (!hasNextEmptyPosition(board, pos)) return true;
            for (int num = 1; num <= SIZE; num++) {
                if (isValid(board, pos, num)) {
                    board[pos.x][pos.y] = num;
                    if (generateFullBoard(board)) return true;
                    board[pos.x][pos.y] = MARKER_EMPTY;
                }
            }
            return false;
        }
        bool isValid(IBoard& board, Position& pos, int num) {
            //check row
            for (int j = 0; j < SIZE; j++) {
                if (board[pos.x][j] == num) return false;
            }

            // check column
            for (int i = 0; i < SIZE; i++) {
                if (board[i][pos.y] == num) return false;
            }

            // check box
            int dx = pos.x - pos.x % BOXSIZE;
            int dy = pos.y - pos.y % BOXSIZE;
            for (int i = 0; i < BOXSIZE; i++) {
                for (int j = 0; j < BOXSIZE; j++) {
                    if (board[dx + i][dy + j] == num) return false;
                }
            }

            return true;
        }
    private:
        bool hasNextEmptyPosition(IBoard& board, Position& pos) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == MARKER_EMPTY) { pos = { i,j }; return true; }
                }
            }
            return false;
        }

        Position randomPosition(IBoard& board) {
            Position pos;
            do {
                pos.x = rand() % 9;
                pos.y = rand() % 9;
            } while (board[pos.x][pos.y] == MARKER_EMPTY);
            return pos;
        }
    };

    class GameBoard {
    private:
        IBoard board;
        SudokuGenerator generator;

    public:
        GameBoard() {
            board.resize(SIZE);
            for (int i = 0; i < SIZE; i++) board[i].resize(SIZE);
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    board[i][j] = MARKER_EMPTY;
                }
            }
        }
        void init() {
            generator.generate(board, SudokuGenerator::Level::MEDIUM);
        }

        void reset() {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    board[i][j] = MARKER_EMPTY;
                }
            }
        }

        bool isDone() {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == MARKER_EMPTY) return false;
                }
            }
            return true;
        }

        IBoard& getRaw() {
            return board;
        }

        string to_string() {
            return ::to_string(board);
        }

        vector<Position> getEmptyPositions() {
            vector<Position> positions;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == MARKER_EMPTY) positions.push_back({ i,j });
                }
            }
            return positions;
        }

        void set(Position pos, int num) {
            board[pos.x][pos.y] = num;
        }

        bool isInvalidState() {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    int num = board[i][j];
                    board[i][j] = MARKER_EMPTY;
                    Position pos(i, j);
                    if (!generator.isValid(board, pos, num)) {
                        board[i][j] = num;
                        return false;
                    }
                    board[i][j] = num;
                }
            }

            return true;
        }
    };

    class Player {
    private:
        GameBoard& board;
        string name;
        stack<Move> history;
        int totalGames = 0;
        int winCounts = 0;
        bool isGameInProgress = false;

    public:
        Player(GameBoard& board) : board(board) {}
        Player(GameBoard& board, string name) : board(board), name(name) {}
        void play() {
            if (!isGameInProgress) {
                isGameInProgress = true; totalGames++;
            }
            vector<Position> positions = board.getEmptyPositions();
            int r = rand() % positions.size();
            auto p = positions[r];
            int num = rand() % 9 + 1;
            board.set(p, num);
        }
        void reset() {
            history = stack<Move>();
        }
        void markWinner() {
            winCounts++;
            cout << "Player " << name << " list the game. Total " << totalGames << ", Wins " << winCounts << endl;
        }
        void markLoser() {
            cout << "Player " << name << " list the game. Total " << totalGames << ", Wins " << winCounts << endl;
        }
        string to_string() {
            // TODO
            stringstream ss;
            return ss.str();
        }
    };

    class Sudoku {
    private:
        GameBoard board;
        Player* player = nullptr;

    public:
        Sudoku() {
            player = new Player(board, "Player1");
        }
        void Play() {
            do {
                board.init();
                while (!board.isDone() && board.isInvalidState()) {
                    player->play();
                }
                DeclareResult(board.isDone());
                Reset();
            } while (ContinueGame());
        }

    private:
        void Init() {
            board.init();
        }
        void Reset() {
            board.reset();
        }
        void DeclareResult(bool res) {
            if (res) {
                player->markWinner();
            }
            else {
                player->markLoser();
            }

            cout << player->to_string();
            cout << board.to_string();
            cout << endl;
        }
        bool ContinueGame() {
            char ch;
            cout << "Continue game??";
            cin >> ch;
            ch = toupper(ch);
            if (ch != 'Y' && ch != 'N') {
                cout << "Didn't get your input." << endl;
                return ContinueGame();
            }
            return ch == 'Y';
        }
    };

    class SudokuGeneratorTester {
    public:
        static void test() {
            GameBoard board;
            SudokuGenerator generator;
            SudokuSolver solver;
            generator.generate(board.getRaw(), SudokuGenerator::Level::MEDIUM);
            cout << board.to_string() << endl;
            cout << solver.hasExtactOneSol(board.getRaw()) << endl;

            gfg_sudoku::GFG_SudokuSolver gfg_solver;
            gfg_solver.SolveSudoku(board.getRaw());
            cout << board.to_string() << endl;
            cout << "Is Board Valid: " << gfg_solver.isValid(board.getRaw()) << endl;
        }
    };

    class SudokuTester {
    public:
        static void test() {
            Sudoku sudoku;
            sudoku.Play();
        }
    };
}