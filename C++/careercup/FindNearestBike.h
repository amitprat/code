#pragma once
#include "../Header.h"

class FindNearestBike {
private:
	class Node {
	public:
		Point point;
		vector<Point> path;

		Node() {}
		Node(Point point) : point(point) {}
		Node(Point point, vector<Point> path) : point(point), path(path) {}

		string to_string() {
			stringstream ss;
			ss << "Point = " << point.to_string() << endl;
			ss << "Path = " << ::to_string(path) << endl;
			ss << "Distance = " << path.size() << endl;
			return ss.str();
		}
	};
public:
	static void test() {
		FindNearestBike obj;
		vector<vector<char>> matrix = {
			{'.', '.', '.', '.', '.', '#'},
			{'.','.','E', '.', '.', '#'},
			{'#', '#', '#' ,'#', '.', '#'},
			{'.','B', '.', '.', '.', '.'},
			{'.', '.', '.', '.','.','B'}
		};
		Point p(1, 2);

		auto result = obj.findNearestBike(matrix, p);
		cout << result.to_string() << endl;
	}

	Node findNearestBike(vector<vector<char>>& matrix, Point start) {
		int n = matrix.size();
		queue<Node> q;
		q.push(Node(start, { start }));
		unordered_set<int> visited;
		visited.insert(start.x * n + start.y);

		while (!q.empty()) {
			auto f = q.front(); q.pop();
			if (isBike(f.point, matrix)) return f;

			auto nbs = neighbours(f.point, visited, matrix);
			for (auto nb : nbs) {
				auto tmp = f.path;
				tmp.push_back(nb);
				q.push(Node(nb, tmp));
				visited.insert(nb.x * n + nb.y);
			}
		}

		return Node();
	}

private:
	bool isBike(Point& p, vector<vector<char>>& matrix) {
		return matrix[p.x][p.y] == 'B';
	}

	vector<Point> neighbours(Point& p, unordered_set<int>& visited, vector<vector<char>>& matrix) {
		vector<Point> result;
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (abs(i) != abs(j)) {
					int posx = p.x + i, posy = p.y + j;
					if (!valid(posx, posy, matrix, visited)) continue;
					result.push_back(Point(posx, posy));
				}
			}
		}
		return result;
	}

	bool valid(int posx, int posy, vector<vector<char>>& matrix, unordered_set<int>& visited) {
		int n = matrix.size();
		int m = matrix[0].size();

		if (posx < 0 || posy < 0 || posx >= n || posy >= m) return false;
		if (visited.find(posx * n + posy) != visited.end()) return false;
		if (matrix[posx][posy] == '#') return false;

		return true;
	}
};