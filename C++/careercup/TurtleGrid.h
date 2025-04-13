#pragma once
#include "../header.h"

/**
 * TurtleGrid
 * ----------
 * Simulates movement on a 2D grid using commands:
 * - 'F': Move Forward
 * - 'L': Turn Left (counter-clockwise)
 * - 'R': Turn Right (clockwise)
 */

class TurtleGrid {
    enum class Direction { North = 0,
                           East = 1,
                           South = 2,
                           West = 3 };
    vector<string> directionStrs;

    const string getDirectionText(Direction dir) const {
        return directionStrs[static_cast<int>(dir)];
    }

   public:
    TurtleGrid() : directionStrs{"North", "East", "South", "West"} {}

    static void test() {
        TurtleGrid obj;
        Point pos(1, 1);
        Direction dir = Direction::North;
        string input = "FFFRRFLF";
        auto [finalPos, finalDir] = obj.getPosition(input, pos, dir);
        cout << "Final pos: " << finalPos.to_string()
             << ", Direction: " << obj.getDirectionText(finalDir) << endl;
    }

    pair<Point, Direction> getPosition(const string& input, Point startPos, Direction startDir) {
        Point pos = startPos;
        Direction dir = startDir;

        for (char ch : input) {
            switch (ch) {
                case 'F':
                    pos = moveForward(pos, dir);
                    break;
                case 'L':
                    dir = turnLeft(dir);
                    break;
                case 'R':
                    dir = turnRight(dir);
                    break;
            }
            cout << "Pos: " << pos.to_string() << ", Dir: " << getDirectionText(dir) << endl;
        }
        return {pos, dir};
    }

   private:
    Point moveForward(Point pos, Direction dir) const {
        switch (dir) {
            case Direction::North:
                pos.y += 1;
                break;
            case Direction::South:
                pos.y -= 1;
                break;
            case Direction::East:
                pos.x += 1;
                break;
            case Direction::West:
                pos.x -= 1;
                break;
        }
        return pos;
    }

    Direction turnLeft(Direction dir) const {
        return static_cast<Direction>((4 + static_cast<int>(dir) - 1) % 4);  // counter-clockwise
    }

    Direction turnRight(Direction dir) const {
        return static_cast<Direction>((4 + static_cast<int>(dir) + 1) % 4);  // clockwise
    }
};
