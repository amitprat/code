#pragma once
#include "../Header.h"

class TurtleGrid
{
	enum class Direction
	{
		North = 1,
		East = 2,
		South = 3,
		West = 4
	};
	vector<string> DirectionStrs;

	const string getTextForEnum(Direction dir)
	{
		return DirectionStrs[(int)dir - 1];
	}

public:
	TurtleGrid()
	{
		DirectionStrs = { "North", "East", "South", "West" };
	}

	static void test()
	{
		TurtleGrid obj;
		Point pos(1, 1);
		Direction dir = Direction::North;
		string input = "FFFRRFLF";
		auto finalPos = obj.getPosition(input, pos, dir);
		cout << "final pos: " << finalPos.first.to_string() << ", Direction: " << obj.getTextForEnum(finalPos.second) << endl;
	}

	pair<Point, Direction> getPosition(string input, Point startPos, Direction startDir)
	{
		Point pos = startPos;
		Direction dir = startDir;

		for (auto ch : input)
		{
			switch (ch)
			{
			case 'F':
				pos = moveForward(pos, dir);
				cout << "Pos: " << pos.to_string() << ", dir: " << getTextForEnum(dir) << endl;
				break;
			case 'L':
				dir = changeDir(dir, Direction::West);
				cout << "Pos: " << pos.to_string() << ", dir: " << getTextForEnum(dir) << endl;
				break;
			case 'R':
				dir = changeDir(dir, Direction::East);
				cout << "Pos: " << pos.to_string() << ", dir: " << getTextForEnum(dir) << endl;
				break;
			}
		}

		return { pos, dir };
	}

	Point moveForward(Point pos, Direction dir)
	{
		switch (dir)
		{
		case Direction::West:
			pos.x -= 1;
			break;
		case Direction::East:
			pos.x += 1;
			break;
		case Direction::North:
			pos.y += 1;
			break;
		case Direction::South:
			pos.y -= 1;
			break;
		}

		return pos;
	}

	Direction changeDir(Direction cur, Direction change)
	{
		switch (change)
		{
		case Direction::West:
			cur = (Direction)((4 + (int)cur - 1) % 4);
			break;
		case Direction::East:
			cur = (Direction)((4 + (int)cur + 1) % 4);
			break;
		}

		return cur;
	}
};