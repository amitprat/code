#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5197964926517248
You need to develop the game Snake. What data structures will you use? Code your solution.

Two parts:
1. 2D plate: 2D array of short, 0 for free, 1 for items to eat, 2 for blocks (including snake body);
2. Snake body: Queue of int pair indicating position like (x, y), every move enqueue new head position and dequeue tail position. Enqueue two nodes if a item eaten. Enqueue and dequeue operation includes set flag in its pixel.

For every move, only constant time (O(1)) needed.
*/

class SnakeGame {
    class Game {
        enum class Dir {
            Up,
            Right,
            Down,
            Left
        };

        struct Snake {
            Point head, tail;
            deque<Point> queue;
            Dir curDir;

            void init(Point start) {
                head = tail = start;
                queue.push_back(start);
                curDir = Dir::Up;
            }
        };

        vector<vector<int>> board;
        Snake snake;

       public:
        Game(int n, Point startPos) {
            board.resize(n, vector<int>(n, 0));
            snake.init(startPos);
            board[startPos.x][startPos.y] = 3;
        }

        void init(int blocks, int food, Point start) {
            int n = board.size();
            srand(time(nullptr));

            while (blocks) {
                int v = rand() % (n * n);
                int r = v / n;
                int c = v % n;

                if (start.x == r && start.y == c) continue;
                if (board[r][c] == 1) continue;
                blocks--;

                board[r][c] = 1;
            }

            while (food) {
                int v = rand() % (n * n);
                int r = v / n;
                int c = v % n;

                if (start.x == r && start.y == c) continue;
                if (board[r][c] == 2) continue;
                food--;

                board[r][c] = 2;
            }
        }

        void move() {
            bool isFood = false;
            switch (snake.curDir) {
                case Dir::Up:
                    snake.head.x = next(snake.head.x, -1);
                    isFood = board[snake.head.x][snake.head.y] == 2;

                    board[snake.head.x][snake.head.y] = 3;
                    snake.queue.push_front(snake.head);

                    removeTail(isFood);
                    break;

                case Dir::Down:
                    snake.head.x = next(snake.head.x, 1);
                    isFood = board[snake.head.x][snake.head.y] == 2;

                    board[snake.head.x][snake.head.y] = 3;
                    snake.queue.push_front(snake.head);

                    removeTail(isFood);
                    break;

                case Dir::Right:
                    snake.head.y = next(snake.head.y, 1);
                    isFood = board[snake.head.x][snake.head.y] == 2;

                    board[snake.head.x][snake.head.y] = 3;
                    snake.queue.push_front(snake.head);

                    removeTail(isFood);
                    break;

                case Dir::Left:
                    snake.head.y = next(snake.head.y, -1);
                    isFood = board[snake.head.x][snake.head.y] == 2;

                    board[snake.head.x][snake.head.y] = 3;
                    snake.queue.push_front(snake.head);

                    removeTail(isFood);
                    break;
            }
        }

        void removeTail(bool isFood) {
            if (!isFood) {
                board[snake.tail.x][snake.tail.y] = 0;
                snake.queue.pop_back();
                snake.tail = snake.queue.back();
            }
        }

        void left() {
            snake.curDir = (Dir)(((int)snake.curDir - 1 + 4) % 4);
        }

        void right() {
            snake.curDir = (Dir)(((int)snake.curDir + 1) % 4);
        }

        int next(int pos, int off) {
            return (pos + off + board.size()) % board.size();
        }

        void print() {
            cout << "---------------------------------------\n";
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[i].size(); j++) {
                    cout << tochar(board[i][j]) << "\t";
                }
                cout << endl;
            }
            cout << "---------------------------------------\n\n";
        }

        char tochar(int num) {
            switch (num) {
                case 0:
                    return 'E';
                case 1:
                    return 'B';
                case 2:
                    return 'F';
                case 3:
                    return 'S';
                default:
                    return num + '0';
            }
        }
    };

   public:
    static void test() {
        Game game(5, {0, 0});
        game.init(4, 10, {0, 0});

        game.print();

        game.move();
        game.right();
        game.move();
        game.move();
        game.move();
        game.left();
        game.move();
        game.move();
        game.move();

        game.print();
    }
};