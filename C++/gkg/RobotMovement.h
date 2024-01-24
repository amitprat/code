#pragma once
#include "../Header.h"

class RobotMovement {
    enum class Direction {
        Up = 0,
        Right,
        Down,
        Left
    };
public:
    static void test() {
        RobotMovement obj;
        string moves = "GLGLGLG";
        cout << obj.isCircular(moves) << endl;
    }

    bool isCircular(string moves) {
        Point<int> start(0, 0);
        Point<int> end = start;
        Direction dir = Direction::Up;

        for (auto ch : moves) {
            switch (ch) {
                case 'G':
                    move(end, dir);
                    break;
                case 'R':
                    dir = (Direction)(((int)dir + 1) % 4);
                    break;
                case 'L':
                    dir = (Direction)(((int)dir + 4 - 1) % 4);
                    break;
            }
            if (start == end) return true;
        }
        return false;
    }

    void move(Point<int>& p, Direction dir) {
        switch (dir) {
            case Direction::Up:
                p.y += 1;
                break;
            case Direction::Right:
                p.x += 1;
                break;
            case Direction::Left:
                p.x -= 1;
                break;
            case Direction::Down:
                p.y -= 1;
                break;
        }
    }
};