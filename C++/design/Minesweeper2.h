#include "../header.h"

class Minesweeper2 {
    struct Cell {
        bool isMine = false;
        bool isRevealed = false;
        bool isFlagged = false;
        int adjacentMines = 0;
    };

    class Board {
        int rows, cols, totalMines;
        vector<vector<Cell>> grid;

       public:
        Board(int r, int c, int mines) : rows(r), cols(c), totalMines(mines) {
            grid.resize(rows, vector<Cell>(cols));
            placeMines();
            calculateAdjacents();
        }

        void placeMines() {
            srand(time(nullptr));
            int placed = 0;
            while (placed < totalMines) {
                int r = rand() % rows;
                int c = rand() % cols;
                if (!grid[r][c].isMine) {
                    grid[r][c].isMine = true;
                    placed++;
                }
            }
        }

        void calculateAdjacents() {
            int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
            int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    if (grid[r][c].isMine) continue;
                    int count = 0;
                    for (int d = 0; d < 8; d++) {
                        int nr = r + dx[d], nc = c + dy[d];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc].isMine)
                            count++;
                    }
                    grid[r][c].adjacentMines = count;
                }
            }
        }

        void reveal(int r, int c) {
            if (!inBounds(r, c) || grid[r][c].isRevealed || grid[r][c].isFlagged) return;
            grid[r][c].isRevealed = true;

            if (grid[r][c].adjacentMines == 0 && !grid[r][c].isMine) {
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        if (dr != 0 || dc != 0)
                            reveal(r + dr, c + dc);
                    }
                }
            }
        }

        bool isMine(int r, int c) const {
            return inBounds(r, c) && grid[r][c].isMine;
        }

        bool isRevealed(int r, int c) const {
            return inBounds(r, c) && grid[r][c].isRevealed;
        }

        bool inBounds(int r, int c) const {
            return r >= 0 && r < rows && c >= 0 && c < cols;
        }

        bool hasWon() const {
            int revealed = 0;
            for (const auto& row : grid)
                for (const auto& cell : row)
                    if (cell.isRevealed) revealed++;
            return revealed == rows * cols - totalMines;
        }

        void print(bool revealAll = false) const {
            cout << "   ";
            for (int c = 0; c < cols; ++c)
                cout << setw(2) << c << " ";
            cout << "\n";

            for (int r = 0; r < rows; ++r) {
                cout << setw(2) << r << " ";
                for (int c = 0; c < cols; ++c) {
                    const Cell& cell = grid[r][c];
                    if (revealAll) {
                        if (cell.isMine) cout << " * ";
                        else cout << " " << cell.adjacentMines << " ";
                    } else if (!cell.isRevealed) {
                        cout << " . ";
                    } else if (cell.isMine) {
                        cout << " * ";
                    } else {
                        cout << " " << cell.adjacentMines << " ";
                    }
                }
                cout << "\n";
            }
        }
    };

    class Game {
        Board board;
        bool gameOver = false;

       public:
        Game(int rows, int cols, int mines) : board(rows, cols, mines) {}

        void run() {
            while (!gameOver) {
                board.print();
                int r, c;
                cout << "Enter row and column (e.g. 3 4): ";
                cin >> r >> c;

                if (board.isMine(r, c)) {
                    cout << "💥 You hit a mine! Game over.\n";
                    board.print(true);
                    gameOver = true;
                } else {
                    board.reveal(r, c);
                    if (board.hasWon()) {
                        cout << "🎉 You won!\n";
                        board.print(true);
                        gameOver = true;
                    }
                }
            }
        }
    };

   public:
    static void test() {
        Game game(9, 9, 10);  // rows, cols, mines
        game.run();
    }
};